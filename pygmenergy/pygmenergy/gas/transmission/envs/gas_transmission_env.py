import gym
from gym import spaces
import numpy as np
import pygmenergy.unetwork.core.env_service_functions_pb2 as envservice
from pygmenergy.unetwork.core import action_pb2, optimization_param_pb2

class GasTransmissionEnv(gym.Env):
    metadata = {'render.modes': ['human']}

    def __init__(self, rpc_service, data_location, task, log_steps=False):
        self._rpc_service = rpc_service
        self._data_location = data_location
        self.log_steps = log_steps

        self._optimization_params = []  # list of ids of optimization params
        self._observation_map = {}  # maps external nodes identifiers from virtual simulator to internal ids of observation

        self._max_reward = 0

        self._compile(task)
        
    @property
    def rpc_service(self):
        return self._rpc_service

    def _compile(self, task):
        self._current_task = task
        self.rpc_service.LoadData(envservice.LoadDataRequest(data_path=self._data_location))
        self.rpc_service.SetCurrentTask(envservice.SetCurrentTaskRequest(task=task))
        env_info = self.rpc_service.GetEnvDescription(envservice.GetEnvDescriptionRequest())
        
        print("Fetching the list of optimization params...\n")
        opt_params_response = self.rpc_service.GetOptimizationParams(envservice.GetOptimizationParamsRequest())
        print(opt_params_response)

        # check whether the env is discrete
        self._is_discrete = env_info.is_discrete 

        self._optimization_params = [param.id for param in opt_params_response.optimization_params]
        print("Optimization params ids: ", self._optimization_params)

        if env_info.is_discrete:
            if (len(self._optimization_params) == 1):
                self.action_space = spaces.Discrete(opt_params_response.optimization_params[0].metadata.discrete_space.n)
            elif (len(self._optimization_params) > 1):
                space = [param.metadata.discrete_space.n for param in opt_params_response.optimization_params]
                self.action_space = spaces.MultiDiscrete(nvec=space)
        else:
            low_values = [
                param.metadata.continuos_space.low_value 
                    for param in opt_params_response.optimization_params
            ]
            high_values = [
                param.metadata.continuos_space.high_value 
                    for param in opt_params_response.optimization_params
            ]
            self.initial_low_values, self.initial_high_values = np.array(low_values), np.array(high_values)

            # if self.symmetrize_actions and not (np.abs(low_values) == high_values).all():
            #     low_values =  [-1.0] * len(low_values)
            #     high_values = [1.0]  * len(high_values)
            # else:
            #     self.symmetrize_actions = False

            self.action_space = spaces.Box(
                low=np.array(low_values), 
                high=np.array(high_values), 
                dtype=np.float16)

        self.observation_space = spaces.Box(
            low=-float('inf'), 
            high=float('inf'), 
            shape=(env_info.observation_space_dimension,), 
            dtype=np.float16)

    def _map_observation(self, env_observation):
        """ Maps from Env_pb2.Observation to tensor.
        
            Args:
                grpc_ob: Env_pb2.Observation object
        """
        # Observation is the state of pressure values in graph's nodes
        if len(self._observation_map) is 0:
            for i, item in enumerate(env_observation.items):
                self._observation_map[item.id] = i

        ob = [None] * (len(env_observation.items))
        for item in env_observation.items:
            idx = self._observation_map[item.id]
            ob[idx] = item.value
        return np.array(ob)

    def reset(self):
        """Resets the state of the environment to an initial state.
        
        Returns:
            numpy.array - initial observation
        """
        self._current_step = 0
        self.total_reward = 0

        result = self.rpc_service.Reset(envservice.ResetRequest())
        if result.reset_status is envservice.ResetResponse.ResetStatus.RESET_FAILED:
            print(result.reset_info)
            return None 
        
        ob = self._map_observation(result.observation)
        self.prev_ob = ob

        return np.array(ob)

    def step(self, action):
        """ Performs one timestep of the environment's dynamics.
        
        Arguments:
            action -- action in the environment, list of float values
        
        Returns:
            new observation, reward for action, whether episode is finished, additional info
        """

        assert self._current_task is not None, "Current task was not set"
        # print("**************** Action is", action)

        self._current_step += 1
        
        rpc_service_action = action_pb2.Action()

        # print(f"Action: {action}")
        acs = action
        if (type(action) is not np.ndarray):
            acs = np.array([acs])

        # for i in range(len(acs)):

        for i in range(acs.size):
            sid = self._optimization_params[i]
            
            opt_param = optimization_param_pb2.OptimizationParameter()
            opt_param.id = sid

            if self._is_discrete:
                opt_param.int_value = acs[i]
            else:
                opt_param.float_value = acs[i]
            
            rpc_service_action.optimization_params.append(opt_param)
                

        # if self.log_steps:
        #    print(f"...step with action {action}")

        response = self.rpc_service.Step(envservice.StepRequest(action=rpc_service_action))

        ob = self._map_observation(response.observation)
        
        if not response.done:
            self.prev_ob = ob
            self.total_reward += response.reward
            # print(f"Step info: {response.info}")
            if self._max_reward < self.total_reward:
                self._max_reward = self.total_reward
                if self.log_steps: 
                    print(f"\n\n********************************** Max reward reached: {self._max_reward} ********************************** \n\n")
        else:
            ob = self.prev_ob
            if self.log_steps: 
                print(f"Total reward in episode is {self.total_reward}")

        return ob, response.reward, response.done, response.info 

    def render(self, mode='human', close=False):
        """Renders the environment to the screen."""
        print(f'Step: {self._current_step}')
        print(f'Total reward: {self.total_reward}')