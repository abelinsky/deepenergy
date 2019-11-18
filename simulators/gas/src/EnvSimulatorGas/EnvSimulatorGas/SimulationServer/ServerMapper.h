#pragma once

#include <grpcpp/grpcpp.h>
#include "unetwork/core/env_service.grpc.pb.h"

namespace SimulationServer
{
	// Maps internal model's objects (domain objects) to protobuf and vice versa
	class ServerMapper
	{
	public:

		// Converts current environment's observation (state) to protobuf 
		static void CurrentObservationToProtobuf(unetwork::Observation*);

		// Converts protobuf task type to internal task type
		static CTrainingTask::TaskType ProtoTaskToInternalTask(unetwork::SystemTask);
	};


	extern void operator << (unetwork::OptimizationParameter&, Objects::OptimizationParam&);
	extern void operator >> (const unetwork::OptimizationParameter&, Objects::OptimizationParam&);
}
