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

	Status SimulationServerImpl::SetDataLocation(::grpc::ServerContext* context, const ::energy_platform::SetDataLocationRequest* request,
		::energy_platform::SetDataLocationResponse* response)
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
		{
			return Status(::grpc::StatusCode::INVALID_ARGUMENT, "Path does not exist (" + path.string() + ")");
		}

		DoLogForced("Data path is set to " + path.string());
		m_pEnv->SetDataLocation(path.string());
		return Status::OK;
	}

	::grpc::Status SimulationServerImpl::SetCurrentTask(::grpc::ServerContext* context, const ::energy_platform::SetCurrentTaskRequest* request,
		::energy_platform::SetCurrentTaskResponse* response)
	{
		CTrainingTask::TaskType Task = ServerMapper::ProtoTaskToInternalTask(request->current_task());
		m_pEnv->SetCurrentTask(Task);
		return Status::OK;
	}

	Status SimulationServerImpl::GetAllowedActions(::grpc::ServerContext* context, const ::energy_platform::AllowedActionsRequest* request,
		::energy_platform::AllowedActionsResponse* response)
	{
		list<ObjectAction*> allowedActions;
		m_pEnv->GetAllowedActions(allowedActions);
		for (auto pObjectAction : allowedActions)
		{
			energy_platform::Action *pAction = response->add_actions();
			pAction->set_uid(pObjectAction->GetUId());
			pAction->set_info(pObjectAction->GetInfo());
			pAction->set_float_value(pObjectAction->Get());
		}
		return Status::OK;
	}

	Status SimulationServerImpl::Reset(::grpc::ServerContext* context, const ::energy_platform::ResetRequest* request,
		::energy_platform::ResetResponse* response)
	{
		string info;
		bool bResult = m_pEnv->Reset(info);
		response->set_reset_info(info);

		if (bResult)
		{
			energy_platform::Observation* pObservation = new energy_platform::Observation;
			ServerMapper::CurrentObservationToProtobuf(pObservation);
			response->set_allocated_observation(pObservation);
		}

		response->set_reset_status(bResult ?
			::energy_platform::ResetResponse_ResetStatus::ResetResponse_ResetStatus_READY_TO_SIMULATE
			: energy_platform::ResetResponse_ResetStatus::ResetResponse_ResetStatus_RESET_FAILED);

		return bResult
			? Status::OK
			: Status(::grpc::StatusCode::INTERNAL, info);
	}

	::grpc::Status SimulationServerImpl::GetEnvDescription(::grpc::ServerContext* context,
		const ::energy_platform::GetEnvDescriptionRequest* request, ::energy_platform::GetEnvDescriptionResponse* response)
	{
		const EnvDescription envDescription = m_pEnv->GetEnvDescription();
		response->set_action_dim(envDescription.m_ActionsNumber);
		response->set_observation_dim(envDescription.m_ObservationSpace);

		// temporary
		if (gData.GetCurrentTask() && gData.GetCurrentTask()->Is(CTrainingTask::SIMPLE))
		{
			response->set_is_discrete(true);
			response->set_discrete_action_dimension((HIGH_ACTION_VALUE - LOW_ACTION_VALUE) * 100 + 1); // 25 discrete actions
		}
		else
		{
			response->set_is_discrete(false);
			response->set_low_action_value(LOW_ACTION_VALUE);
			response->set_high_action_value(HIGH_ACTION_VALUE);
			response->set_low_observation_value(19.);
			response->set_high_observation_value(100.);
		}

		return Status::OK;
	}

	Status SimulationServerImpl::Step(::grpc::ServerContext* context, const ::energy_platform::StepRequest* request,
		::energy_platform::StepResponse* response)
	{
		// xxx
		for (int i = 0; i < request->actions_size(); i++)
		{
			energy_platform::Action action = request->actions(i);
			
			// temp
			RManagedParam *pParam = GetModel()->m_ControlParams[action.uid()];
			if (gData.GetCurrentTask() && !gData.GetCurrentTask()->Is(CTrainingTask::SIMPLE))
			{
				double value = action.float_value();
				pParam->Set(value);
			}
			else
			{
				double value =  double(action.int_value()) * 0.01 + LOW_ACTION_VALUE;
				pParam->Set(value);
				DoLogForced("Step with action " + ftos(value));
			}			
		}
		SimulationStepResults Results;

		bool bResult = m_pEnv->Step(&Results);
		response->set_info(Results.m_Info);
		response->set_reward(Results.m_Reward);
		response->set_done(Results.m_bDone);

		if (!Results.m_bDone)
		{
			energy_platform::Observation* pObservation = new energy_platform::Observation;
			ServerMapper::CurrentObservationToProtobuf(pObservation);
			response->set_allocated_observation(pObservation);
		}

		return Status::OK;
		/*return bResult
			? Status::OK
			: Status(::grpc::StatusCode::INTERNAL, "Simulation failed. See logs.");*/
	}

	Status SimulationServerImpl::Stop(::grpc::ServerContext* context, const ::energy_platform::StopRequest* request,
		::energy_platform::StopResponse* response)
	{
		m_pEnv->StopSimulations();
		return Status::OK;
	}
}