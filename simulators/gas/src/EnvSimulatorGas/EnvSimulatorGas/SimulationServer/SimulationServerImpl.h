#pragma once

#include <grpcpp/grpcpp.h>
#include "energyplatform/core/env_service.grpc.pb.h"
#include "GasEnv.h"

using namespace Core;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using energyplatform::EnvService;

namespace SimulationServer
{
	class SimulationServerImpl final : public EnvService::Service
	{
	public:
		SimulationServerImpl();
		~SimulationServerImpl();

		virtual ::grpc::Status LoadData(::grpc::ServerContext* context, const ::energyplatform::LoadDataRequest* request, 
			::energyplatform::LoadDataResponse* response) override;

		::grpc::Status GetEnvDescription(::grpc::ServerContext* context, 
			const ::energyplatform::GetEnvDescriptionRequest* request, ::energyplatform::GetEnvDescriptionResponse* response) override;

		::grpc::Status SetCurrentTask(::grpc::ServerContext* context, const ::energyplatform::SetCurrentTaskRequest* request,
			::energyplatform::SetCurrentTaskResponse* response) override;

		virtual ::grpc::Status GetOptimizationParams(::grpc::ServerContext* context, 
			const ::energyplatform::GetOptimizationParamsRequest* request, ::energyplatform::GetOptimizationParamsResponse* response) override;

		::grpc::Status Reset(::grpc::ServerContext* context, const ::energyplatform::ResetRequest* request,
			::energyplatform::ResetResponse* response) override;

		::grpc::Status Step(::grpc::ServerContext* context, const ::energyplatform::StepRequest* request,
			::energyplatform::StepResponse* response) override;

		virtual ::grpc::Status Stop(::grpc::ServerContext* context, const ::energyplatform::StopRequest* request,
			::energyplatform::StopResponse* response) override;

		CGasEnv* GetEnv() { return m_pEnv; }

	protected:
		CGasEnv* m_pEnv;
	};
}

