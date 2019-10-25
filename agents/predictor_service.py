
import grpc
from concurrent import futures

from energyplatform.core.action_pb2 import Action
from energyplatform.core.optimization_param_pb2 import OptimizationParameter

import energyplatform.core.predictor_service_pb2 as ps
import energyplatform.core.predictor_service_pb2_grpc as ps_grpc

from stable_baselines import TD3, DDPG, A2C, PPO2, SAC, TRPO

class PredictorServicer(ps_grpc.PredictorServiceServicer):
    """Provides methods that implement functionality of predictor servicer """
    
    def __init__(self, model_location):
        # Load the trained agent
        self.model = PPO2.load(model_location)
        self._observation_map = {} # maps external nodes identifiers from virtual simulator to internal ids of observation

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

    def Predict(self, request, context):
        print("Predicting actions for observation: ", request.observation)
        ob = self._map_observation(request.observation)
        action_values, _states = self.model.predict(ob)
        print("\n***************** Result ******************** \n", action_values)

        grpc_action = Action()
        for i, value in enumerate(action_values):
            opt_param = OptimizationParameter() 
            opt_param.id = f"{i}"
            opt_param.float_value = value
            grpc_action.optimization_params.append(opt_param)

        return ps.PredictReponse(action=grpc_action)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    ps_grpc.add_PredictorServiceServicer_to_server(
        PredictorServicer("models/21-10-2019_11-45-23.pkl"), server
    )
    server.add_insecure_port('[::]:50052')
    server.start()
    print("Predictor service started at localhost:50052")
    while (True):
        continue
    print("Predictor service stopped")
    
if __name__ == "__main__":
    serve()


