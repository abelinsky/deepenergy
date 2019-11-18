#pragma once

#include <grpcpp/grpcpp.h>
#include "unetwork/core/env_service.grpc.pb.h"
#include "GasEnv.h"

using namespace Core;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using unetwork::EnvService;

namespace SimulationServer
{
	class SimulationServerImpl final : public EnvService::Service
	{
	public:
		SimulationServerImpl();
		~SimulationServerImpl();

		virtual ::grpc::Status LoadData(::grpc::ServerContext* context, const ::unetwork::LoadDataRequest* request,
			::unetwork::LoadDataResponse* response) override;

		::grpc::Status GetEnvDescription(::grpc::ServerContext* context, 
			const ::unetwork::GetEnvDescriptionRequest* request, ::unetwork::GetEnvDescriptionResponse* response) override;

		::grpc::Status SetCurrentTask(::grpc::ServerContext* context, const ::unetwork::SetCurrentTaskRequest* request,
			::unetwork::SetCurrentTaskResponse* response) override;

		virtual ::grpc::Status GetOptimizationParams(::grpc::ServerContext* context, 
			const ::unetwork::GetOptimizationParamsRequest* request, ::unetwork::GetOptimizationParamsResponse* response) override;

		::grpc::Status Reset(::grpc::ServerContext* context, const ::unetwork::ResetRequest* request,
			::unetwork::ResetResponse* response) override;

		::grpc::Status Step(::grpc::ServerContext* context, const ::unetwork::StepRequest* request,
			::unetwork::StepResponse* response) override;

		virtual ::grpc::Status Stop(::grpc::ServerContext* context, const ::unetwork::StopRequest* request,
			::unetwork::StopResponse* response) override;

		CGasEnv* GetEnv() { return m_pEnv; }

	protected:
		CGasEnv* m_pEnv;
	};
}

