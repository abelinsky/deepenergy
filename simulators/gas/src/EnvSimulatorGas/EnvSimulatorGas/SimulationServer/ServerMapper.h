#pragma once

#include <grpcpp/grpcpp.h>
#include "energyplatform/core/env_service.grpc.pb.h"

namespace SimulationServer
{
	// Maps internal model's objects (domain objects) to protobuf and vice versa
	class ServerMapper
	{
	public:

		// Converts current environment's observation (state) to protobuf 
		static void CurrentObservationToProtobuf(energyplatform::Observation*);

		// Converts protobuf task type to internal task type
		static CTrainingTask::TaskType ProtoTaskToInternalTask(energyplatform::SystemTask);
	};


	extern void operator << (energyplatform::OptimizationParameter&, Objects::OptimizationParam&);
	extern void operator >> (const energyplatform::OptimizationParameter&, Objects::OptimizationParam&);
}
