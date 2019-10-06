import gym
from gym import spaces

import numpy as np

import grpc
import energyplatform.core.env_service_pb2 
import energyplatform.core.env_service_pb2_grpc
import energyplatform.core.env_service_functions_pb2 as envservice
from energyplatform.core.action_pb2 import Action
from energyplatform.core.optimization_param_pb2 import OptimizationParameter

class EnvGas(gym.Env):
    """ Wrapper over  energyplatform.core.env_service_pb2_grpc.EnvServiceStub object.
        Follows gym interface.
    """
    metadata = {'render.modes': ['human']}
    
    def __init__(self, 
                env_service,
                data_location,
                log_steps=False
        ):
        super(EnvGas, self).__init__()
        self.env_service = env_service
        self._data_location = data_location
        self.log_steps = log_steps

        self._optimization_params = [] # list of ids of optimization params
        self._observation_map = {} # maps external nodes identifiers from virtual simulator to internal ids of observation
        
        # self._compile()
        self._max_reward = 0

    def compile(self, task):
        self._current_task = task
        self.env_service.LoadData(envservice.LoadDataRequest(data_path=self._data_location))
        env_info = self.env_service.GetEnvDescription(envservice.GetEnvDescriptionRequest())
        opt_params_response = self.env_service.GetOptimizationParams(envservice.GetOptimizationParamsRequest())
        self._is_discrete = env_info.is_discrete 

        self._optimization_params = [param.id for param in opt_params_response.optimization_params]
        print("Optimization params ids: ", self._optimization_params)

        if env_info.is_discrete:
            return NotImplementedError
        else:
            low_values = [
                param.metadata.continuos_space.low_value 
                    for param in opt_params_response.optimization_params
            ]
            high_values = [
                param.metadata.continuos_space.high_value 
                    for param in opt_params_response.optimization_params
            ]
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
        return ob

    def reset(self):
        """
            Resets the state of the environment to an initial state
        """ 
        self._current_step = 0
        self.total_reward = 0

        result = self.env_service.Reset(envservice.ResetRequest())
        if result.reset_status is envservice.ResetResponse.ResetStatus.RESET_FAILED:
            print(result.reset_info)
            return None 
        
        ob = self._map_observation(result.observation)
        self.prev_ob = ob

        return ob
    
    def step(self, action):
        """ Performs one timestep of the environment's dynamics.
        
        Arguments:
            action -- action in the environment, list of float values
        
        Returns:
            new observation
            reward for action
            whether episode is finished
            additional info
        """
        assert self._current_task is not None, "Current task was not set"
        # print("**************** Action is", action)

        self._current_step += 1
        
        env_service_action = Action()

        # print(f"Action: {action}")

        if self._is_discrete:
            return NotImplementedError
            # for i in range(len(action)):
            #     proto_action = self._action_map[i]  # Env_pb2.Action
            #     proto_action.float_value = action[i]
            #     step_params.actions.append(proto_action)
        else:
            # temp
            for i in range(len(action)):
                sid = self._optimization_params[i]
                
                opt_param = OptimizationParameter()
                opt_param.id = sid
                opt_param.float_value = action[i]
                
                env_service_action.optimization_params.append(opt_param)
                

        if self.log_steps:
            print(f"...step with action {action}")

        response = self.env_service.Step(envservice.StepRequest(action=env_service_action))

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
        """Renders the environment to the screen
        """
        print(f'Step: {self._current_step}')
        print(f'Total reward: {self.total_reward}')
