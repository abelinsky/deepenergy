#pragma once

#include <grpcpp/grpcpp.h>
#include "grpc/Env.grpc.pb.h"

namespace SimulationServer
{
	// Maps internal model's objects (domain objects) to protobuf and vice versa
	class ServerMapper
	{
	public:

		// Converts current environment's observation (state) to protobuf 
		static void CurrentObservationToProtobuf(energy_platform::Observation*);

		// Converts protobuf task type to internal task type
		static CTrainingTask::TaskType ProtoTaskToInternalTask(energy_platform::Task);
	};
}
