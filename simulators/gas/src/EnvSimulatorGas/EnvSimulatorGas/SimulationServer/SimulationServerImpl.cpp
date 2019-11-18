#include "pch.h"
#include "SimulationServerImpl.h"
#include "ServerMapper.h"

namespace SimulationServer
{
	// temporary
	double LOW_ACTION_VALUE = 0.75;
	double HIGH_ACTION_VALUE = 1.10;

	SimulationServerImpl::SimulationServerImpl()
	{
		m_pEnv = new CGasEnv;
	}

	SimulationServerImpl::~SimulationServerImpl()
	{
		delete m_pEnv;
	}

	Status SimulationServerImpl::LoadData(::grpc::ServerContext* context, const ::unetwork::LoadDataRequest* request,
		::unetwork::LoadDataResponse* response)
	{
		DoLogForced("Seeking for data in: " + request->data_path());

		fs::path path(request->data_path());
		if (path.empty())
			return Status(::grpc::StatusCode::INVALID_ARGUMENT, "You must specify data path for simulator initialization");

		if (!fs::exists(path))
		{
			path = fs::current_path() / path;
			DoLogForced("Path was not found. Seeking for data in: " + path.string());
		}

		if (!fs::exists(path))
			return Status(::grpc::StatusCode::INVALID_ARGUMENT, "Path does not exist (" + path.string() + ")");

		DoLogForced("Loading data from " + path.string());
		bool bResult = m_pEnv->LoadData(path.string());

		response->set_status(bResult
			? unetwork::LoadDataResponse::LoadDataStatus::LoadDataResponse_LoadDataStatus_OK
			: unetwork::LoadDataResponse::LoadDataStatus::LoadDataResponse_LoadDataStatus_FAILED
		);

		return bResult
			? Status::OK
			: Status(::grpc::StatusCode::INTERNAL, "Failed to load data, see server logs.");
	}

	::grpc::Status SimulationServerImpl::GetEnvDescription(::grpc::ServerContext* context,
		const ::unetwork::GetEnvDescriptionRequest* request, ::unetwork::GetEnvDescriptionResponse* response)
	{
		EnvDescription envDescription = m_pEnv->GetEnvDescription();
		
		response->set_action_space_dimension(envDescription.m_OpimizationParamsNumber);
		response->set_is_discrete(envDescription.m_bDiscrete);
		response->set_observation_space_dimension(envDescription.m_ObservationSpace);

		return Status::OK;
	}

	::grpc::Status SimulationServerImpl::SetCurrentTask(::grpc::ServerContext* context, const ::unetwork::SetCurrentTaskRequest* request,
		::unetwork::SetCurrentTaskResponse* response)
	{
		CTrainingTask::TaskType Task = ServerMapper::ProtoTaskToInternalTask(request->task());
		m_pEnv->SetCurrentTask(Task);
		return Status::OK;
	}

	Status SimulationServerImpl::GetOptimizationParams(::grpc::ServerContext* context, const ::unetwork::GetOptimizationParamsRequest* request,
		::unetwork::GetOptimizationParamsResponse* response)
	{
		list<OptimizationParam*> optParams;
		m_pEnv->GetOptimizationParams(optParams);
		for (auto pOptParam : optParams)
		{
			unetwork::OptimizationParameter *pParam = response->add_optimization_params();
			(*pParam) << (*pOptParam);
		}
		return Status::OK;
	}

	Status SimulationServerImpl::Reset(::grpc::ServerContext* context, const ::unetwork::ResetRequest* request,
		::unetwork::ResetResponse* response)
	{
		string info;
		bool bResult = m_pEnv->Reset(info);
		response->set_reset_info(info);

		if (bResult)
		{
			unetwork::Observation* pObservation = new unetwork::Observation;
			ServerMapper::CurrentObservationToProtobuf(pObservation);
			response->set_allocated_observation(pObservation);
		}

		response->set_reset_status(bResult ?
			::unetwork::ResetResponse_ResetStatus::ResetResponse_ResetStatus_READY_TO_SIMULATE
			: unetwork::ResetResponse_ResetStatus::ResetResponse_ResetStatus_RESET_FAILED);

		return bResult
			? Status::OK
			: Status(::grpc::StatusCode::INTERNAL, info);
	}

	Status SimulationServerImpl::Step(::grpc::ServerContext* context, const ::unetwork::StepRequest* request,
		::unetwork::StepResponse* response)
	{
		string log = "Step with action: ";
		for (int i = 0; i < request->action().optimization_params_size(); i++)
		{
			unetwork::OptimizationParameter eParam = request->action().optimization_params(i);
			RManagedParam *pParam = GetModel()->m_ControlParams[eParam.id()];
			eParam >> (*pParam);
			log += ftos(pParam->Get()) + " ";
		}
		DoLogForced(log);
		
		SimulationStepResults Results;

		bool bResult = m_pEnv->Step(&Results, false);

		response->set_reward(Results.m_Reward);
		response->set_done(Results.m_bDone);
		response->set_info(Results.m_Info);

		if (!Results.m_bDone)
		{
			unetwork::Observation* pObservation = new unetwork::Observation;
			ServerMapper::CurrentObservationToProtobuf(pObservation);
			response->set_allocated_observation(pObservation);
		}

		return Status::OK;
	}

	Status SimulationServerImpl::Stop(::grpc::ServerContext* context, const ::unetwork::StopRequest* request,
		::unetwork::StopResponse* response)
	{
		m_pEnv->StopSimulations();
		return Status::OK;
	}
}