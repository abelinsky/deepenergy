import os
import time
import numpy as np

import energyplatform.core.env_service_pb2
from energyplatform.core.env_service_pb2_grpc import EnvServiceStub
import energyplatform.core.env_service_pb2_grpc
import energyplatform.core.tasks_pb2 as tasks

from energyplatform.core.env_service_pb2_grpc import EnvServiceStub
 
import gym
from gym import spaces

import grpc
from env4gas import EnvGas

from pygma.rl.reinforce import agent

import json
# import tensorflow as tf
# from tensorboard import main as tb

def train_agent(data_location):
    # ================== Setup channel ================= #
    channel = grpc.insecure_channel('localhost:50051')
    # ================== Train model ================== #
    
    # The algorithms require a vectorized environment to run
    env = EnvGas(EnvServiceStub(channel), data_location, log_steps=True, symmetrize_actions=False)
    env.compile(task=tasks.SIMPLE)

    # env_list = DummyVecEnv([lambda: env])

    # Because we use parameter noise, we should use a MlpPolicy with layer normalization
    tb_log_dir = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'model_tensorboard')

    # model = SAC(MlpPolicy, env, verbose=1, tensorboard_log=tb_log_dir)
    # model = PPO2(MlpPolicy, env_list, verbose=1, tensorboard_log=tb_log_dir)
    # model.learn(total_timesteps=1000000)

    agent_ = agent.ReinforceAgent(env, max_rollout_length=100)
    agent_.run_training_loop(1000)

    # save model
    model_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'models')
    if not (os.path.exists(model_path)):
        os.makedirs(model_path)
    
    model_name = time.strftime("%d-%m-%Y_%H-%M-%S")
    model_file = os.path.join(model_path, model_name)
    # model.save(model_file)

    with open(f'{model_file}.metadata.json', 'w') as metadata:
        json.dump(env.action_ids, metadata, indent=4)
        
    channel.close()

def inference(data_location, model_location):
    channel = grpc.insecure_channel('localhost:50051')
    env = EnvGas(EnvServiceStub(channel), data_location)
    
    # Load the trained agent
    # model = PPO2.load(model_location)

    # Use trained agent
    ob = env.reset()
    for _ in range(1000):
        # action, _states = model.predict(ob)
        ob, _, done, _ = env.step(action)
        env.render()
        if done:
            env.total_reward = 0
    
    channel.close()

def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--data', type=str, default='Simulation/')
    parser.add_argument('--inf', action='store_true')
    parser.add_argument('--model', type=str)
    args = parser.parse_args()
    
    print("******************* Args: ", args)

    if args.inf:
        inference(args.data, args.model)
    else:  
        train_agent(args.data)
    

if __name__ == "__main__":
    main()