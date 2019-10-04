#pragma once

#include <grpcpp/grpcpp.h>
#include "grpc/Env.grpc.pb.h"
#include "GasEnv.h"

using namespace Core;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using energy_platform::Env;
using energy_platform::Env;

namespace SimulationServer
{
	class SimulationServerImpl final : public Env::Service
	{
	public:
		SimulationServerImpl();
		~SimulationServerImpl();

		grpc::Status SetDataLocation(::grpc::ServerContext* context, const ::energy_platform::SetDataLocationRequest* request, 
			::energy_platform::SetDataLocationResponse* response) override;

		::grpc::Status GetEnvDescription(::grpc::ServerContext* context, 
			const ::energy_platform::GetEnvDescriptionRequest* request, ::energy_platform::GetEnvDescriptionResponse* response) override;

		::grpc::Status SetCurrentTask(::grpc::ServerContext* context, const ::energy_platform::SetCurrentTaskRequest* request,
			::energy_platform::SetCurrentTaskResponse* response) override;

		::grpc::Status GetAllowedActions(::grpc::ServerContext* context, const ::energy_platform::AllowedActionsRequest* request,
			::energy_platform::AllowedActionsResponse* response) override;

		::grpc::Status Reset(::grpc::ServerContext* context, const ::energy_platform::ResetRequest* request,
			::energy_platform::ResetResponse* response) override;

		::grpc::Status Step(::grpc::ServerContext* context, const ::energy_platform::StepRequest* request,
			::energy_platform::StepResponse* response) override;

		virtual ::grpc::Status Stop(::grpc::ServerContext* context, const ::energy_platform::StopRequest* request,
			::energy_platform::StopResponse* response) override;

		CGasEnv* GetEnv() { return m_pEnv; }

	protected:
		CGasEnv* m_pEnv;
	};
}

