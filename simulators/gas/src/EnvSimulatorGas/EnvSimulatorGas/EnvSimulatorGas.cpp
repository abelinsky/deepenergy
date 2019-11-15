// EnvSimulatorGas.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// #prag﻿ma comment(linke﻿r, "/subsystem:"windows" /entry:"﻿mainCRTStartup"" ﻿)﻿﻿﻿

#include "pch.h"
#include <iostream>
#include "TCHAR.h"
#include "GasEnv.h"
#include "utils.h"
#include "SimulationServerImpl.h"

#include <grpcpp/grpcpp.h>
#include "energyplatform/core/predictor_service.grpc.pb.h"
#include "ServerMapper.h"
#include "BIn.h"

using namespace std;
using namespace SimulationServer;

void RunSimulationServer() 
{
	string server_address("0.0.0.0:50051");
	SimulationServerImpl simulationService;
	
	ServerBuilder builder;
	// Listen on the given address without any authentication mechanism.
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	// Register "service" as the instance through which we'll communicate with
	// clients. In this case it corresponds to an *synchronous* service.
	builder.RegisterService(&simulationService);
	// Finally assemble the server.
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;

	// Wait for the server to shutdown. Note that some other thread must be
	// responsible for shutting down the server for this call to ever return.
	server->Wait();

	// releaase resources
	simulationService.GetEnv()->StopSimulations();
}


/************************************************** Kafka consumer (real-time serving) ***********************************************/
#include <librdkafka/rdkafkacpp.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <cstring>

static bool run = true;
static bool exit_eof = false;

static void sigterm(int sig) {
	run = false;
}

bool msg_consume(RdKafka::Message* message, float& msg_value) {
	bool result = false;
	const RdKafka::Headers *headers;

	switch (message->err()) {
		case RdKafka::ERR__TIMED_OUT:
			break;

		case RdKafka::ERR_NO_ERROR:
		{
			/* Real message */
			std::cout << "Read msg at offset " << message->offset() << std::endl;
			if (message->key()) {
				std::cout << "Key: " << *message->key() << std::endl;
			}
			headers = message->headers();
			if (headers) {
				std::vector<RdKafka::Headers::Header> hdrs = headers->get_all();
				for (size_t i = 0; i < hdrs.size(); i++) {
					const RdKafka::Headers::Header hdr = hdrs[i];

					if (hdr.value() != NULL)
						printf(" Header: %s = \"%.*s\"\n",
							hdr.key().c_str(),
							(int)hdr.value_size(), (const char *)hdr.value());
					else
						printf(" Header:  %s = NULL\n", hdr.key().c_str());
				}
			}
			const char* value = static_cast<const char *>(message->payload());
			msg_value = atof(value);
			printf("%.*s\n",
				static_cast<int>(message->len()),
				value);
			result = true;
			break;
		}

		case RdKafka::ERR__PARTITION_EOF:
		{
			/* Last message */
			if (exit_eof) {
				run = false;
			}
			break;
		}

		case RdKafka::ERR__UNKNOWN_TOPIC:
		case RdKafka::ERR__UNKNOWN_PARTITION:
		{
			std::cerr << "Consume failed" << message->errstr() << std::endl;
			std::cerr << "Consumer will be stopped" << std::endl;
			run = false;
			break;
		}

		default:
		{
			/* Errors */
			std::cerr << "Consume failed: " << message->errstr() << std::endl;
			std::cerr << "Consumer will be stopped" << std::endl;
			run = false;
		}
	}

	return result;
}

void RunKafkaConsumer(CGasEnv* env, std::unique_ptr<energyplatform::PredictorService::Stub> &predictor_service)
{
	// std::string brokers = "localhost"; // localhost:9092
	std::string brokers = "localhost:9092";
	std::string errstr;
	std::string topic_str = "telemetry";
	std::string mode = "C"; // consumer mode
	std::string debug;
	int32_t partition = 0; // RdKafka::Topic::PARTITION_UA;
	int64_t start_offset = RdKafka::Topic::OFFSET_END;
	bool do_conf_dump = false;

	// create configuration objects
	RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
	RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

	// set configuration properties
	conf->set("metadata.broker.list", brokers, errstr);

	signal(SIGINT, sigterm);
	signal(SIGTERM, sigterm);

	// consumer mode
	conf->set("enable.partition.eof", "true", errstr);
	RdKafka::Consumer *consumer = RdKafka::Consumer::create(conf, errstr);
	if (!consumer) {
		std::cerr << "Failed to create kafka consumer: " << errstr << std::endl;
		exit(1);
	}
	std::cout << "% Created kafka consumer " << consumer->name() << std::endl;
		
	// create topic handle
	RdKafka::Topic *topic = RdKafka::Topic::create(consumer, topic_str,
		tconf, errstr);
	if (!topic) {
		std::cerr << "Failed to create topic: " << errstr << std::endl;
		exit(1);
	}

	//  Start consumer for topic+partition at start offset
	RdKafka::ErrorCode resp = consumer->start(topic, partition, start_offset);
	if (resp != RdKafka::ERR_NO_ERROR) {
		std::cerr << "Failed to start consumer: " <<
			RdKafka::err2str(resp) << std::endl;
		exit(1);
	}

	int current_stratum = 0;
	// consume messages
	while (true) {
		// cout << "consuming messages ...";
		RdKafka::Message *msg = consumer->consume(topic, partition, 1000);
		float value = 0;
		if (msg_consume(msg, value)) {
			// temp: perturb P 
			BIn *pObject = dynamic_cast<BIn*>(GetModel()->m_Ins[0]);
			double p = pObject->m_P;
			pObject->m_P += value * 0.25; // scale
			std::cout << "Step with changed Pressure on In object: changed from " << p << " to " << pObject->m_P << std::endl;

			env->StepServingModel(predictor_service, current_stratum);
		}

		delete msg;
		consumer->poll(0);
	}

	/* Stop consumer */
	consumer->stop(topic, partition);
	consumer->poll(1000);
	delete topic;
	delete consumer;

	delete conf;
	delete tconf;

	/*
	 * Wait for RdKafka to decommission.
	 * This is not strictly needed (when check outq_len() above), but
	 * allows RdKafka to clean up all its resources before the application
	 * exits so that memory profilers such as valgrind wont complain about
	 * memory leaks.
	 */
	RdKafka::wait_destroyed(5000);

	cout << "End serving ...";
}

#ifndef NO_WINDOW

#pragma comment(linker, "/subsystem:console")
int main(int argc, char* argv[])
{
	//RunKafkaConsumer();
	//return 0;
#ifdef _DEBUG
	
	bool bServingMode = true;

	if (bServingMode) {
		// Test serving mode
		string arg0 = string(argv[0]);
		delete [] argv;

		argc = 3;
		string args[3] = { string(arg0), "101", "Data\\" };
		argv = new char*[3];
		for (int i = 0; i < 3; i++) {
			int sz = args[i].size();
			argv[i] = new char[args[i].size()];
			strcpy_s(argv[i], std::strlen(args[i].c_str())+1, args[i].c_str());
		}

		SetCurrentDirectory("C:\\Users\\ab\\AppData\\Roaming\\Vesta\\");
	}
	else {
		// Test training mode
		SetCurrentDirectory("C:\\Users\\ab\\AppData\\Roaming\\Vesta\\Data\\");
	}
	
#endif

	for (int i = 0; i < argc; i++)
		std::cout << "Param " << i << ": " << argv[i] << std::endl;

	if (argc >= 2)
	{
		// serving model
		char buff[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, buff);
		string current_dir(buff);
		
		gData.m_DataDir = (fs::path(current_dir)/fs::path(argv[2])).string();
		DoLogForced("Fetching data from " + gData.m_DataDir);

		gData.m_Mode = Mode::RECOMMENDATION_SERVICE;
		std::cout << "Serving trained model..." << endl;
		

		// Initialize predictor service client
		std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel("localhost:50052",
			grpc::InsecureChannelCredentials());
		std::unique_ptr<energyplatform::PredictorService::Stub> predictor_stub = energyplatform::PredictorService::NewStub(channel);

		// Create environment
		CGasEnv *env = new CGasEnv;
		env->PrepareForModelServing();
		RunKafkaConsumer(env, predictor_stub);
		delete env;
		
		// env->ServeTrainedModel();
	}
	else
	{
		char buff[MAX_PATH];
		GetModuleFileName(NULL, buff, MAX_PATH);
		SetCurrentDirectory(fs::path(buff).parent_path().string().c_str());

		gData.m_Mode = Mode::TRAINING_SERVICE;
		std::cout << "Training model..." << endl;

		// training 
		RunSimulationServer();
	}
	return 0; 
}

#else

#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
INT __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	RunServer();
	return 0;
}

#endif