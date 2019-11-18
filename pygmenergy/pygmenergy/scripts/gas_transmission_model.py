# Copyright (c) 2019 Alexander Belinsky

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ==============================================================================
"""Script for training gas transmission system model."""

import os
import time
import grpc

import pygmenergy.unetwork.core.tasks_pb2 as tasks
from pygmenergy.unetwork.core import env_service_pb2_grpc as rpc_stub 

import gym
import pygmenergy.gas.transmission.envs
from pygma.rl.reinforce import agent as reinforce

def main():

    env_name = 'gas-transmission-v0'

    # create data dir
    data_path = os.path.join(os.path.dirname(
        os.path.realpath(__file__)), '../data')

    if not os.path.exists(data_path):
        os.makedirs(data_path)

    # create log dir
    log_prefix = 'pg_'
    logdir = log_prefix + env_name + '_' + time.strftime('%d-%m-%Y_%H-%M-%S')
    logdir = os.path.join(data_path, logdir)

    # set data location
    data_location = 'data/'

    # setup grpc channel
    channel = grpc.insecure_channel('localhost:50051')

    # create and compile environment
    env = gym.make('gas-transmission-v0', 
        rpc_service=rpc_stub.EnvServiceStub(channel),
        data_location=data_location,
        task=tasks.SIMPLE
    )
    # env.compile(task=tasks.SIMPLE)

    n_iter = 1000
    agent = reinforce.ReinforceAgent(
        env,
        reward_to_go=True,
        baseline=True,
        actor_n_layers=2,
        actor_layers_size=64,
        min_batch_size=500,
        log_metrics=True,
        logdir=logdir,
        render_freq=10,
        eval_batch_size=30
    )
    agent.run_training_loop(n_iter)

if __name__ == "__main__":
    main()