#include "pch.h"
#include "ServerMapper.h"
#include "BIn.h"
#include "BOut.h"

namespace SimulationServer
{
	void ServerMapper::CurrentObservationToProtobuf(energyplatform::Observation *pObservation)
	{
		for (auto pObject : GetModel()->m_Ins)
		{
			BIn *pIn = dynamic_cast<BIn*>(pObject);
			assert(pIn);

			energyplatform::PhysicalParam *pParam = pObservation->add_items();
			string sid = (boost::format("%d__P") % pIn->m_ID).str();
			pParam->set_id(sid);
			pParam->set_type(energyplatform::PhysicalValueType::PV_PRESSURE);
			pParam->set_value(pIn->m_rP);
		}

		for (auto pObject : GetModel()->m_Outs)
		{
			BOut *pOut = dynamic_cast<BOut*>(pObject);
			assert(pOut);

			energyplatform::PhysicalParam *pParam = pObservation->add_items();
			string sid = (boost::format("%d__P") % pOut->m_ID).str();
			pParam->set_id(sid);
			pParam->set_type(energyplatform::PhysicalValueType::PV_PRESSURE);
			pParam->set_value(pOut->m_rP);
		}
	}

	CTrainingTask::TaskType ServerMapper::ProtoTaskToInternalTask(energyplatform::SystemTask ProtoTask)
	{
		CTrainingTask::TaskType Task;
		switch (ProtoTask)
		{
		case energyplatform::SystemTask::FEED_FORWARD:
			Task = CTrainingTask::TaskType::FEED_FORWARD;
			break;
		case energyplatform::SystemTask::AVAILABLE_TECHNOLOGICAL_MODE:
			Task = CTrainingTask::TaskType::AVAILABLE_TECHNOLOGICAL_MODE;
			break;
		case energyplatform::SystemTask::MAX_THROUGHPUT:
			Task = CTrainingTask::TaskType::MAX_THROUGHPUT;
			break;
		case energyplatform::SystemTask::SIMPLE:
			Task = CTrainingTask::TaskType::SIMPLE;
			break;
		default:
			Task = CTrainingTask::TaskType::UNDEFINED;
			break;
		}
		return Task;
	}

	inline void operator << (energyplatform::OptimizationParameter &eParam, Objects::OptimizationParam &iParam)
	{
		eParam.set_id(iParam.GetUId());

		eParam.mutable_metadata()->set_type(iParam.IsDiscrete() 
			? energyplatform::ParameterType::PT_DISCRETE
			: energyplatform::ParameterType::PT_CONTINUOUS);

		energyplatform::PhysicalValueType vtype = energyplatform::PhysicalValueType::PV_NOTYPE;
		switch (iParam.m_Code)
		{
		case OParam::O_OB:
			vtype = energyplatform::PhysicalValueType::PV_FREQUENCY;
			break;
		default:
			break;
		}
		eParam.mutable_metadata()->set_physical_type(vtype);

		if (!iParam.IsDiscrete())
		{
			double min = 0, max = 0;
			iParam.GetParamBorders(min, max);
			eParam.mutable_metadata()->mutable_continuos_space()->set_low_value(min);
			eParam.mutable_metadata()->mutable_continuos_space()->set_high_value(max);
			// Set value
			eParam.set_float_value(iParam.Get());
		}
		else
		{
			// TODO: discrete type
		}

		eParam.set_info(iParam.GetInfo());
	}
}