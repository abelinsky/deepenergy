// EnvSimulatorGas.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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

void RunServer() 
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

#ifndef NO_WINDOW

#pragma comment(linker, "/subsystem:console")
int main(int argc, char* argv[])
{
	char buff[MAX_PATH];
	GetModuleFileName(NULL, buff, MAX_PATH);
	SetCurrentDirectory(fs::path(buff).parent_path().string().c_str());

	RunServer();
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