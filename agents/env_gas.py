import gym
from gym import spaces

import numpy as np

import grpc
import Env_pb2
import Env_pb2_grpc

class GasEnv(gym.Env):
    """ Wrapper over Env_pb2_grpc.EnvStub object.
        Follows gym interface.
    """
    metadata = {'render.modes': ['human']}
    
    def __init__(self, 
                grpc_env,
                data_location,
                log_steps=False
        ):
        super(GasEnv, self).__init__()
        self.grpc_env = grpc_env
        self.grpc_env.SetDataLocation(Env_pb2.SetDataLocationRequest(data_path=data_location))

        self._observation_map = {} # maps external nodes identifiers from virtual simulator to internal ids of observation
        self._action_map = {} # maps internal ids of actions to Env_pb2.Action objects
        # self._compile()
        self._max_reward = 0
        self.log_steps = log_steps
        self._current_task = None
        self._is_discrete = False

    def compile(self, task):
        """Compiles environment.
        
        Arguments:
            task {[grpc task]} -- task to be solved
        """
        self._current_task = task
        self.grpc_env.SetCurrentTask(Env_pb2.SetCurrentTaskRequest(current_task=task))
        env_info = self.grpc_env.GetEnvDescription(Env_pb2.GetEnvDescriptionRequest())
        self._is_discrete = env_info.is_discrete 

        if env_info.is_discrete:
            self.action_space = spaces.Discrete(env_info.discrete_action_dimension)
        else:
            self.action_space = spaces.Box(
                low=env_info.low_action_value, 
                high=env_info.high_action_value, 
                shape=(env_info.action_dim,), 
                dtype=np.float16)

        self.observation_space = spaces.Box(
            low=env_info.low_observation_value, 
            high=env_info.high_observation_value, 
            shape=(env_info.observation_dim,), 
            dtype=np.float16)

        # Build actions map
        response = self.grpc_env.GetAllowedActions(Env_pb2.AllowedActionsRequest())
        print(f"_________ Allowed actions")
        for index, action in enumerate(response.actions):
            print(f"____________ Allowed action # {index}: {action}")
            self._action_map[index] = action

    def _map_observation(self, grpc_ob):
        """ Maps from Env_pb2.Observation to tensor.
        
            Args:
                grpc_ob: Env_pb2.Observation object
        """
        # if len(self._observation_map) is 0:
        #     for index, node in enumerate(grpc_ob.nodes):
        #         self._observation_map[node.uid] = index

        #     start_from = len(self._observation_map)
        #     for index, edge in enumerate(grpc_ob.edges):
        #         self._observation_map[edge.uid] = index + start_from

        # ob = [None] * (len(grpc_ob.nodes)) # + len(grpc_ob.edges))
        # for node in grpc_ob.nodes:
        #     ob_index = self._observation_map[node.uid]
        #     for node_param in node.node_params:
        #         if node_param.param_type is Env_pb2.NodeParams.ParamType.P:
        #             ob[ob_index] = node_param.param_value

        # Observation is the state of pressure values in graph's nodes
        if len(self._observation_map) is 0:
            for index, node in enumerate(grpc_ob.nodes):
                self._observation_map[node.uid] = index

        ob = [None] * (len(grpc_ob.nodes))
        for node in grpc_ob.nodes:
            ob_index = self._observation_map[node.uid]
            for node_param in node.node_params:
                if node_param.param_type is Env_pb2.NodeParams.ParamType.P:
                    ob[ob_index] = node_param.param_value

        return ob

    def reset(self):
        """
            Resets the state of the environment to an initial state
        """ 
        self._current_step = 0
        self.total_reward = 0

        result = self.grpc_env.Reset(Env_pb2.ResetRequest())
        if result.reset_status is Env_pb2.ResetResponse.ResetStatus.RESET_FAILED:
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
        step_params = Env_pb2.StepRequest()

        # print(f"Action: {action}")

        if not self._is_discrete:
            for i in range(len(action)):
                proto_action = self._action_map[i]  # Env_pb2.Action
                proto_action.float_value = action[i]
                step_params.actions.append(proto_action)
        else:
            # temp
            proto_action = self._action_map[0]
            proto_action.int_value = action
            step_params.actions.append(proto_action)

        if self.log_steps:
            print(f"...step with action {action}")

        response = self.grpc_env.Step(step_params)
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
