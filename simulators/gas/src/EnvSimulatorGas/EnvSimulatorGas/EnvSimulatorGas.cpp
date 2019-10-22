﻿// EnvSimulatorGas.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// #prag﻿ma comment(linke﻿r, "/subsystem:"windows" /entry:"﻿mainCRTStartup"" ﻿)﻿﻿﻿

#include "pch.h"
#include <iostream>
#include "TCHAR.h"
#include "GasEnv.h"
#include "utils.h"
#include "SimulationServerImpl.h"

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

class ExampleEventCb : public RdKafka::EventCb {
public:
	void event_cb(RdKafka::Event &event) {
		switch (event.type())
		{
		case RdKafka::Event::EVENT_ERROR:
			if (event.fatal()) {
				std::cerr << "FATAL ";
				run = false;
			}
			std::cerr << "ERROR (" << RdKafka::err2str(event.err()) << "): " <<
				event.str() << std::endl;
			break;

		case RdKafka::Event::EVENT_STATS:
			std::cerr << "\"STATS\": " << event.str() << std::endl;
			break;

		case RdKafka::Event::EVENT_LOG:
			fprintf(stderr, "LOG-%i-%s: %s\n",
				event.severity(), event.fac().c_str(), event.str().c_str());
			break;

		default:
			std::cerr << "EVENT " << event.type() <<
				" (" << RdKafka::err2str(event.err()) << "): " <<
				event.str() << std::endl;
			break;
	}
  }
};

void msg_consume(RdKafka::Message* message, void* opaque) {
	const RdKafka::Headers *headers;

	switch (message->err()) {
	case RdKafka::ERR__TIMED_OUT:
		break;

	case RdKafka::ERR_NO_ERROR:
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
		printf("%.*s\n",
			static_cast<int>(message->len()),
			static_cast<const char *>(message->payload()));
		break;

	case RdKafka::ERR__PARTITION_EOF:
		/* Last message */
		if (exit_eof) {
			run = false;
		}
		break;

	case RdKafka::ERR__UNKNOWN_TOPIC:
	case RdKafka::ERR__UNKNOWN_PARTITION:
		std::cerr << "Consume failed: " << message->errstr() << std::endl;
		run = false;
		break;

	default:
		/* Errors */
		std::cerr << "Consume failed: " << message->errstr() << std::endl;
		run = false;
	}
}

void RunKafkaConsumer()
{
	// std::string brokers = "localhost"; // localhost:9092
	std::string brokers = "localhost:9092";
	std::string errstr;
	std::string topic_str = "telemetry";
	std::string mode = "C"; // consumer mode
	std::string debug;
	int32_t partition = 0; // RdKafka::Topic::PARTITION_UA;
	int64_t start_offset = RdKafka::Topic::OFFSET_BEGINNING;
	bool do_conf_dump = false;

	// create configuration objects
	RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
	RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

	// set configuration properties
	conf->set("metadata.broker.list", brokers, errstr);

	// create callback object
	ExampleEventCb ex_event_cb;
	conf->set("event_cb", &ex_event_cb, errstr);

	signal(SIGINT, sigterm);
	signal(SIGTERM, sigterm);

	if (mode == "C") {
		// consumer mode
		conf->set("enable.partition.eof", "true", errstr);
		RdKafka::Consumer *consumer = RdKafka::Consumer::create(conf, errstr);
		if (!consumer) {
			std::cerr << "Failed to create consumer: " << errstr << std::endl;
			exit(1);
		}
		std::cout << "% Created consumer " << consumer->name() << std::endl;
		
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

		// consume messages
		while (run) {
			RdKafka::Message *msg = consumer->consume(topic, partition, 1000);
			msg_consume(msg, NULL);
			delete msg;

			consumer->poll(0);
		}

		/* Stop consumer */
		consumer->stop(topic, partition);
		consumer->poll(1000);
		delete topic;
		delete consumer;
	}

	delete conf;
	delete tconf;

	RdKafka::wait_destroyed(5000);
}

#ifndef NO_WINDOW

#pragma comment(linker, "/subsystem:console")
int main(int argc, char* argv[])
{
	RunKafkaConsumer();
	return 0;

	/* ==================================================================== */
	char buff[MAX_PATH];
	GetModuleFileName(NULL, buff, MAX_PATH);
	SetCurrentDirectory(fs::path(buff).parent_path().string().c_str());

	for (int i = 0; i < argc; i++)
		std::cout << "Param " << i << ": " << argv[i] << std::endl;

	if (argc > 1 && argv[1] == "serve")
	{
		// serving
		RunKafkaConsumer();
	}
	else
	{
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