#include "pch.h"
#include "ServerMapper.h"
#include "BIn.h"
#include "BOut.h"
#include "BShop.h"

namespace SimulationServer
{
	void ServerMapper::CurrentObservationToProtobuf(unetwork::Observation *pObservation)
	{
		for (auto pObject : GetModel()->m_Ins)
		{
			BIn *pIn = dynamic_cast<BIn*>(pObject);
			assert(pIn);

			unetwork::PhysicalParam *pParam = pObservation->add_items();
			string sid = (boost::format("%d__P") % pIn->m_ID).str();
			pParam->set_id(sid);
			pParam->set_type(unetwork::PhysicalValueType::PV_PRESSURE);
			pParam->set_value(pIn->m_rP);
		}

		for (auto pObject : GetModel()->m_Outs)
		{
			BOut *pOut = dynamic_cast<BOut*>(pObject);
			assert(pOut);

			unetwork::PhysicalParam *pParam = pObservation->add_items();
			string sid = (boost::format("%d__P") % pOut->m_ID).str();
			pParam->set_id(sid);
			pParam->set_type(unetwork::PhysicalValueType::PV_PRESSURE);
			pParam->set_value(pOut->m_rP);
		}

		if (EXPERIMENT > 1) {
			for (auto pObject : GetModel()->m_Shops)
			{
				unetwork::PhysicalParam *pParam = pObservation->add_items();
				string sid = (boost::format("%d__Pin") % pObject->m_ID).str();
				pParam->set_id(sid);
				pParam->set_type(unetwork::PhysicalValueType::PV_PRESSURE);
				pParam->set_value(pObject->m_rPin);

				pParam = pObservation->add_items();
				sid = (boost::format("%d__Pout") % pObject->m_ID).str();
				pParam->set_id(sid);
				pParam->set_type(unetwork::PhysicalValueType::PV_PRESSURE);
				pParam->set_value(pObject->m_rPout);
			}
		}
	}

	CTrainingTask::TaskType ServerMapper::ProtoTaskToInternalTask(unetwork::SystemTask ProtoTask)
	{
		CTrainingTask::TaskType Task;
		switch (ProtoTask)
		{
		case unetwork::SystemTask::FEED_FORWARD:
			Task = CTrainingTask::TaskType::FEED_FORWARD;
			break;
		case unetwork::SystemTask::AVAILABLE_TECHNOLOGICAL_MODE:
			Task = CTrainingTask::TaskType::AVAILABLE_TECHNOLOGICAL_MODE;
			break;
		case unetwork::SystemTask::MAX_THROUGHPUT:
			Task = CTrainingTask::TaskType::MAX_THROUGHPUT;
			break;
		case unetwork::SystemTask::SIMPLE:
			Task = CTrainingTask::TaskType::SIMPLE;
			break;
		default:
			Task = CTrainingTask::TaskType::UNDEFINED;
			break;
		}
		return Task;
	}

	inline void operator<<(unetwork::OptimizationParameter &eParam, Objects::OptimizationParam &iParam)
	{
		eParam.set_id(iParam.GetUId());

		bool bDiscrete = iParam.IsDiscrete();
		eParam.mutable_metadata()->set_type(bDiscrete
			? unetwork::ParameterType::PT_DISCRETE
			: unetwork::ParameterType::PT_CONTINUOUS);

		unetwork::PhysicalValueType vtype = unetwork::PhysicalValueType::PV_NOTYPE;
		switch (iParam.m_Code)
		{
		case OParam::O_OB:
			vtype = unetwork::PhysicalValueType::PV_FREQUENCY;
			break;
		default:
			break;
		}
		eParam.mutable_metadata()->set_physical_type(vtype);

		if (bDiscrete)
		{
			// temp, test discrete space
			double min = 0, max = 0;
			iParam.GetParamBorders(min, max);
			int n = int((max - min) * 100);
			eParam.mutable_metadata()->mutable_discrete_space()->set_n(n);
			eParam.set_int_value(0);
		}
		else
		{
			double min = 0., max = 0.;
			iParam.GetParamBorders(min, max);
			eParam.mutable_metadata()->mutable_continuos_space()->set_low_value(min);
			eParam.mutable_metadata()->mutable_continuos_space()->set_high_value(max);
			eParam.set_float_value(iParam.Get());
		}

		eParam.set_info(iParam.GetInfo());
	}

	void operator>>(const unetwork::OptimizationParameter &eParam, Objects::OptimizationParam &iParam)
	{
		bool discrete = iParam.IsDiscrete();

		double min = 0, max = 0;
		iParam.GetParamBorders(min, max);
		iParam.Set(discrete
			? min + float(eParam.int_value()) / 100.
			: eParam.float_value());
	}
}