#include "pch.h"
#include "ServerMapper.h"
#include "BIn.h"
#include "BOut.h"

namespace SimulationServer
{
	void ServerMapper::CurrentObservationToProtobuf(energy_platform::Observation *pObservation)
	{
		for (auto pObject : GetModel()->m_Ins)
		{
			BIn *pIn = dynamic_cast<BIn*>(pObject);
			assert(pIn);

			energy_platform::Node *pNode = pObservation->add_nodes();
			pNode->set_uid(pIn->m_Node);

			// Add node's pressure value
			energy_platform::NodeParams *pParam = pNode->add_node_params();
			pParam->set_param_type(energy_platform::NodeParams_ParamType::NodeParams_ParamType_P);
			pParam->set_param_value(pIn->m_rP);

			// Add node's temperature value
			pParam = pNode->add_node_params();
			pParam->set_param_type(energy_platform::NodeParams_ParamType::NodeParams_ParamType_T);
			pParam->set_param_value(pIn->m_rT);
		}

		for (auto pObject : GetModel()->m_Outs)
		{
			BOut *pOut = dynamic_cast<BOut*>(pObject);
			assert(pOut);

			energy_platform::Node *pNode = pObservation->add_nodes();
			pNode->set_uid(pOut->m_Node);

			// Add node's pressure value
			energy_platform::NodeParams *pParam = pNode->add_node_params();
			pParam->set_param_type(energy_platform::NodeParams_ParamType::NodeParams_ParamType_P);
			pParam->set_param_value(pOut->m_rP);

			// Add node's temperature value
			pParam = pNode->add_node_params();
			pParam->set_param_type(energy_platform::NodeParams_ParamType::NodeParams_ParamType_T);
			pParam->set_param_value(pOut->m_rT);
		}

		//for (auto modelNode : GetModel()->GetConnectionsMatrix().GetNodes())
		//{
		//	energy_platform::Node *pNode = pObservation->add_nodes();
		//	pNode->set_uid(modelNode.second->m_ID);

		//	// Add node's pressure value
		//	energy_platform::NodeParams *pParam = pNode->add_node_params();
		//	pParam->set_param_type(energy_platform::NodeParams_ParamType::NodeParams_ParamType_P);
		//	pParam->set_param_value(modelNode.second->m_rP);

		//	// Add node's temperature value
		//	pParam = pNode->add_node_params();
		//	pParam->set_param_type(energy_platform::NodeParams_ParamType::NodeParams_ParamType_T);
		//	pParam->set_param_value(modelNode.second->m_rT);
		//}

		//for (auto pObject : GetModel()->GetPipes())
		//{
		//	energy_platform::Edge *pEdge = pObservation->add_edges();
		//	pEdge->set_uid(pObject->m_ID);

		//	// Add value
		//	energy_platform::EdgeParams *pParam = pEdge->add_edge_params();
		//	pParam->set_param_type(energy_platform::EdgeParams_ParamType::EdgeParams_ParamType_Q);
		//	pParam->set_param_value(pObject->m_rQin);
		//}			
	}

	CTrainingTask::TaskType ServerMapper::ProtoTaskToInternalTask(energy_platform::Task ProtoTask)
	{
		CTrainingTask::TaskType Task;
		switch (ProtoTask)
		{
		case energy_platform::Task::FEED_FORWARD:
			Task = CTrainingTask::TaskType::FEED_FORWARD;
			break;
		case energy_platform::Task::AVAILABLE_TECHNOLOGICAL_MODE:
			Task = CTrainingTask::TaskType::AVAILABLE_TECHNOLOGICAL_MODE;
			break;
		case energy_platform::Task::MAX_THROUGHPUT:
			Task = CTrainingTask::TaskType::MAX_THROUGHPUT;
			break;
		case energy_platform::Task::SIMPLE:
			Task = CTrainingTask::TaskType::SIMPLE;
			break;
		default:
			Task = CTrainingTask::TaskType::UNDEFINED;
			break;
		}
		return Task;
	}
}