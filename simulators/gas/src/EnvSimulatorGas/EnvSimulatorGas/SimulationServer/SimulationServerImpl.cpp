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

	Status SimulationServerImpl::LoadData(::grpc::ServerContext* context, const ::energyplatform::LoadDataRequest* request,
		::energyplatform::LoadDataResponse* response)
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
			? energyplatform::LoadDataResponse::LoadDataStatus::LoadDataResponse_LoadDataStatus_OK
			: energyplatform::LoadDataResponse::LoadDataStatus::LoadDataResponse_LoadDataStatus_FAILED
		);

		return bResult
			? Status::OK
			: Status(::grpc::StatusCode::INTERNAL, "Failed to load data, see server logs.");
	}

	::grpc::Status SimulationServerImpl::GetEnvDescription(::grpc::ServerContext* context,
		const ::energyplatform::GetEnvDescriptionRequest* request, ::energyplatform::GetEnvDescriptionResponse* response)
	{
		const EnvDescription envDescription = m_pEnv->GetEnvDescription();
		
		response->set_action_space_dimension(envDescription.m_OpimizationParamsNumber);
		response->set_is_discrete(envDescription.m_bDiscrete);
		response->set_observation_space_dimension(envDescription.m_ObservationSpace);

		return Status::OK;
	}

	::grpc::Status SimulationServerImpl::SetCurrentTask(::grpc::ServerContext* context, const ::energyplatform::SetCurrentTaskRequest* request,
		::energyplatform::SetCurrentTaskResponse* response)
	{
		CTrainingTask::TaskType Task = ServerMapper::ProtoTaskToInternalTask(request->task());
		m_pEnv->SetCurrentTask(Task);
		return Status::OK;
	}

	Status SimulationServerImpl::GetOptimizationParams(::grpc::ServerContext* context, const ::energyplatform::GetOptimizationParamsRequest* request, 
		::energyplatform::GetOptimizationParamsResponse* response)
	{
		list<OptimizationParam*> optParams;
		m_pEnv->GetOptimizationParams(optParams);
		for (auto pOptParam : optParams)
		{
			energyplatform::OptimizationParameter *pParam = response->add_optimization_params();
			(*pParam) << (*pOptParam);
		}
		return Status::OK;
	}

	Status SimulationServerImpl::Reset(::grpc::ServerContext* context, const ::energyplatform::ResetRequest* request,
		::energyplatform::ResetResponse* response)
	{
		string info;
		bool bResult = m_pEnv->Reset(info);
		response->set_reset_info(info);

		if (bResult)
		{
			energyplatform::Observation* pObservation = new energyplatform::Observation;
			ServerMapper::CurrentObservationToProtobuf(pObservation);
			response->set_allocated_observation(pObservation);
		}

		response->set_reset_status(bResult ?
			::energyplatform::ResetResponse_ResetStatus::ResetResponse_ResetStatus_READY_TO_SIMULATE
			: energyplatform::ResetResponse_ResetStatus::ResetResponse_ResetStatus_RESET_FAILED);

		return bResult
			? Status::OK
			: Status(::grpc::StatusCode::INTERNAL, info);
	}

	Status SimulationServerImpl::Step(::grpc::ServerContext* context, const ::energyplatform::StepRequest* request,
		::energyplatform::StepResponse* response)
	{
		string log = "Step with action: ";
		for (int i = 0; i < request->action().optimization_params_size(); i++)
		{
			energyplatform::OptimizationParameter eParam = request->action().optimization_params(i);
			RManagedParam *pParam = GetModel()->m_ControlParams[eParam.id()];
			pParam->Set(eParam.float_value());
			
			log += ftos(eParam.float_value()) + " ";
		}
		DoLog(log);
		
		SimulationStepResults Results;

		bool bResult = m_pEnv->Step(&Results);

		response->set_reward(Results.m_Reward);
		response->set_done(Results.m_bDone);
		response->set_info(Results.m_Info);

		if (!Results.m_bDone)
		{
			energyplatform::Observation* pObservation = new energyplatform::Observation;
			ServerMapper::CurrentObservationToProtobuf(pObservation);
			response->set_allocated_observation(pObservation);
		}

		return Status::OK;
	}

	Status SimulationServerImpl::Stop(::grpc::ServerContext* context, const ::energyplatform::StopRequest* request,
		::energyplatform::StopResponse* response)
	{
		m_pEnv->StopSimulations();
		return Status::OK;
	}
}