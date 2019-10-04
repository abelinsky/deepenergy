import os
import time
import numpy as np

import grpc
import Env_pb2
import Env_pb2_grpc

import gym
from gym import spaces

from env_gas import GasEnv

from stable_baselines.common.policies import MlpPolicy
from stable_baselines.common.vec_env import DummyVecEnv
from stable_baselines import TD3, DDPG, A2C, PPO2, SAC, TRPO
from stable_baselines.ddpg import AdaptiveParamNoiseSpec
from stable_baselines.ddpg.policies import LnMlpPolicy

def train_agent(data_location):
    # ================== Setup channel ================= #
    channel = grpc.insecure_channel('localhost:50051')

    # ================== Train model ================== #
    
    # The algorithms require a vectorized environment to run
    env = DummyVecEnv([
        lambda: GasEnv(Env_pb2_grpc.EnvStub(channel), data_location, log_steps=True)]
        )

    # Because we use parameter noise, we should use a MlpPolicy with layer normalization
    model = PPO2(MlpPolicy, env, verbose=1, tensorboard_log="./model_tensorboard/")

    # model = TRPO(MlpPolicy, env, verbose=1, tensorboard_log="./model_tensorboard/")
    model.learn(total_timesteps=50000)

    # save model
    model_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'models')
    if not (os.path.exists(model_path)):
        os.makedirs(model_path)
    
    model_name = time.strftime("%d-%m-%Y_%H-%M-%S")
    model_file = os.path.join(model_path, model_name)
    model.save(model_file)

    # obs = env.reset()
    # for i in range(2000):
    #    action, _states = model.predict(obs)
    #    obs, rewards, done, info = env.step(action)
    #    env.render()
        
    channel.close()

def inference(data_location, model_location):
    channel = grpc.insecure_channel('localhost:50051')
    env = GasEnv(Env_pb2_grpc.EnvStub(channel), data_location)
    
    # Load the trained agent
    model = PPO2.load(model_location)

    # Use trained agent
    ob = env.reset()
    for i in range(1000):
        action, _states = model.predict(ob)
        ob, reward, done, info = env.step(action)
        env.render()
        if done:
            env.total_reward = 0
    
    channel.close()

def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--data', type=str, default='data/')
    parser.add_argument('--inf', action='store_true')
    parser.add_argument('--model', type=str)
    args = parser.parse_args()
    
    print("args: ", args)
    if args.inf:
      inference(args.data, args.model)
    else:  
        train_agent(args.data)
    
if __name__ == "__main__":
    main()