#include "pch.h"
#include "ConnectionsMatrix.h"
#include "Objects.h"

namespace Connections
{

CConnectionsMatrix::CConnectionsMatrix(void)
{
	m_EdgesCount = 0;
	m_nLineElements = 0;
	m_MaxID = 0;
	m_MaxNodeID = 0;
}

CConnectionsMatrix::~CConnectionsMatrix(void)
{
	Clear();
}

void CConnectionsMatrix::Clear()
{
	for (unordered_map <int, CNode*>::iterator i = m_Nodes.begin(); i != m_Nodes.end(); i++)
	{
		CNode *pNode = i->second;
		delete pNode;
	}
	m_Nodes.clear();
}

void CConnectionsMatrix::AddNode(CNode *pNode)
{
	m_Nodes[pNode->m_ID] = pNode;
}

CNode* CConnectionsMatrix::EraseNode(int NodeID)
{
	unordered_map <int, CNode*>::iterator i = m_Nodes.find(NodeID);
	if (i != m_Nodes.end())
	{
		CNode *pNode = i->second;
		m_Nodes.erase(i);
		return pNode;
	}
	return NULL;
}

CNode* CConnectionsMatrix::GetNode(int NodeID)
{
	if (m_Nodes.find(NodeID) == m_Nodes.end())
		return NULL;
	return m_Nodes[NodeID];
}

bool CConnectionsMatrix::LoadData(istream &in, string &Error, unordered_map<int, int> *pMapChange)
{
	CObjectsModel *pModel = GetModel();

	Clear();
	int nNodesCount;

	in >> m_EdgesCount;
	in >> nNodesCount;
	in >> m_nLineElements;

	string s;
	getline(in, s);

	for (int i = 0; i<m_EdgesCount; i++)	// считывание ребер
	{
		int ID, Type;
		in >> ID;
		in >> Type;

		m_MaxID = max(m_MaxID, ID);

		if (pMapChange && (pMapChange->find(ID) != pMapChange->end()))
			Type = (*pMapChange)[ID];

		switch (Type)
		{
		case 0: // открытый кран
			{
				BValve *pValve = new BValve;
				pValve->m_ID = ID;
				pModel->AddObject(pValve);
				break;
			}
		case 1: // труба
			{
				BPipe *pPipe = new BPipe;
				pPipe->m_ID = ID;
				pModel->AddObject(pPipe);
				break;
			}
		case 2: // КЦ
			{
				BShop *pShop = new BShop;
				pShop->m_ID = ID;
				pModel->AddObject(pShop);
				break;
			}
		case 3: // кран регулятор или байпас
			{
				BRDValve *pValve = new BRDValve;
				pValve->m_ID = ID;
				pModel->AddObject(pValve);
				break;
			}
		case 4: // объект локальных потерь давления
			{
				BLost *pLost = new BLost;
				pLost->m_ID = ID;
				pModel->AddObject(pLost);
				break;
			}
		case 5: // АВО
			{
				BShopGPA *pShopGPA = new BShopGPA;
				pShopGPA->m_ID = ID;
				pModel->AddObject(pShopGPA);
				break;
			}
		case 6: // ГПА
			{
				BShopAVO *pShopAVO = new BShopAVO;
				pShopAVO->m_ID = ID;
				pModel->AddObject(pShopAVO);				
				break;
			}
		default:
			{
				Error = (boost::format("Неизвестный тип объекта в файле MatrixConnections.dat (%d)")% Type).str();
				return false;
			}
		}

		getline(in, s);
	}

	for (int i = 0; i<nNodesCount; i++)	// считывание узлов
	{
		int NodeID;
		in >> NodeID;
		CNode *pNode = new CNode;
		pNode->m_ID = NodeID;
		m_MaxNodeID = max(m_MaxNodeID, NodeID);

		AddNode(pNode);

		for (int j = 0; j<m_nLineElements; j++)
		{
			int EdgeID;
			in >> EdgeID;
			if (EdgeID == 0)
				break;
			if (EdgeID<0)
			{
				pNode->AddEdgeIn(pModel->GetObject(abs(EdgeID)));
			}
			if (EdgeID>0)
			{
				pNode->AddEdgeOut(pModel->GetObject(EdgeID));
			}
		}

		getline(in, s);
	}

	return true;
}

void CConnectionsMatrix::PrintExportData(ostream &out)
{
	CObjectsModel *pModel = GetModel();
	m_EdgesCount = 0;
	for (list <BObject*>::iterator i = pModel->m_ObjectsList.begin(); i != pModel->m_ObjectsList.end(); i++)
	{
		BObject *pObject = *i;
		if (pObject->CanExport())
			m_EdgesCount++;
	}

	out <<
		m_EdgesCount	<< " " <<
		m_Nodes.size()	<< " " << 
		m_nLineElements << 
		endl;
	
	for (list <BObject*>::iterator i = pModel->m_ObjectsList.begin(); i != pModel->m_ObjectsList.end(); i++)
	{
		BObject *pObject = *i;
		if (!pObject->CanExport())
			continue;
		out << 
			pObject->m_ID << " " <<
			pObject->GetMatrixID() <<
			endl;
	}

	for (unordered_map <int, CNode*>::iterator i = m_Nodes.begin(); i != m_Nodes.end(); i++)
	{
		CNode *pNode = i->second;
		out <<
			pNode->m_ID;

		int ElemsCount = m_nLineElements;
		// притоки в узел
		for (vector <int>::iterator j = pNode->m_InEdges.begin(); j != pNode->m_InEdges.end(); j++)
		{
			BObject *pObject = pModel->GetObject(*j);
			assert(pObject);
			if (!pObject->CanExport())
				continue;
			int ID = -(*j);
			out << " " << ID;
			ElemsCount--;
		}
		// отборы из узла
		for (vector <int>::iterator j = pNode->m_OutEdges.begin(); j != pNode->m_OutEdges.end(); j++)
		{
			BObject *pObject = pModel->GetObject(*j);
			assert(pObject);
			if (!pObject->CanExport())
				continue;
			int ID = (*j);
			out << " " << ID;
			ElemsCount--;
		}
		// заполнение нулями
		for (int j = 1; j<=ElemsCount; j++)
		{
			out << " " << "0";
		}

		out << endl;
	}
}

bool CConnectionsMatrix::GetEdges(int NodeStart, int NodeEnd, list <int> &ResultList)
{
	CNode *pNodeStart = GetNode(NodeStart);
	CNode *pNodeEnd = GetNode(NodeEnd);

	for (vector <int>::iterator i = pNodeStart->m_OutEdges.begin(); i != pNodeStart->m_OutEdges.end(); i++)
	{
		int EOut = *i;
		for (vector <int>::iterator j = pNodeEnd->m_InEdges.begin(); j != pNodeEnd->m_InEdges.end(); j++)
		{
			int EIn = *j;
			if (EOut == EIn)
			{
				ResultList.push_back(EIn);
			}
		}
	}

	return !ResultList.empty();
}

void CConnectionsMatrix::Clone(CConnectionsMatrix &DestinationMatrix)
{
	DestinationMatrix.m_EdgesCount = m_EdgesCount;
	DestinationMatrix.m_nLineElements = m_nLineElements;
	for (unordered_map <int, CNode*>::iterator i = m_Nodes.begin(); i != m_Nodes.end(); i++)
	{
		CNode *pSourceNode = i->second;
		CNode *pDestinationNode = new CNode;
		pSourceNode->Attach(pDestinationNode);
		DestinationMatrix.AddNode(pDestinationNode);
	}
}

void CConnectionsMatrix::AddEdge(BObject *pObject)
{
	m_EdgesCount++;
	CNode *pNodeStart = GetNode(pObject->m_NodeStart);
	CNode *pNodeEnd = GetNode(pObject->m_NodeEnd);
	if (!pNodeStart)
	{
		pNodeStart = new CNode(pObject->m_NodeStart);
		AddNode(pNodeStart);
	}
	if (!pNodeEnd)
	{
		pNodeEnd = new CNode(pObject->m_NodeEnd);
		AddNode(pNodeEnd);
	}
	pNodeStart->AddEdgeOut(pObject->m_ID);
	pNodeEnd->AddEdgeIn(pObject->m_ID);

	m_nLineElements = max<int>(m_nLineElements, pNodeStart->m_InEdges.size()+pNodeStart->m_OutEdges.size());
}

void CConnectionsMatrix::PostObjectsLoad()
{
	CObjectsModel *pModel = &gData.m_Model;
	for (unordered_map <int, CNode*>::iterator i = m_Nodes.begin(); i != m_Nodes.end(); i++)
	{
		CNode *pNode = i->second;
		pNode->PostObjectsLoad();
	}
	
	{
		// Формирование групп КЦ, объединенных на входе и выходе (включая трубы обвязки КЦ)
		struct RShopNodes
		{
			RShopNodes(void){}
			RShopNodes(list <int>& NodesStart, list <int>& NodesEnd)
			{
				m_NodesStart = NodesStart;
				m_NodesEnd = NodesEnd;
			}

			void operator = (const RShopNodes& Source)
			{
				m_NodesStart = Source.m_NodesStart;
				m_NodesEnd = Source.m_NodesEnd;
			}
			list <int> m_NodesStart;
			list <int> m_NodesEnd;
		};
		map <RShopsGroup*, RShopNodes> Groups;

		for (vector <BObject*>::iterator i = pModel->m_Shops.begin(); i != pModel->m_Shops.end(); i++)
		{
			BShop *pShop = dynamic_cast<BShop*>(*i);
			CNode *pStartNode = GetNode(pShop->m_NodeStart);
			CNode *pEndNode = GetNode(pShop->m_NodeEnd);
			assert(pStartNode);
			assert(pEndNode);

			list <int> ShopStartNodes, ShopEndNodes;
			ShopStartNodes.push_back(pStartNode->m_ID);
			ShopEndNodes.push_back(pEndNode->m_ID);

			// StartNode
			{
				list<int> Edges;
				pStartNode->CollectEdges(Edges);
				for (list<int>::iterator j = Edges.begin(); j != Edges.end(); j++)
				{
					BObject *pObject = pModel->GetObject(*j);
					if (!pObject)
						continue;
					BPipe *pPipe = dynamic_cast<BPipe*>(pObject);
					if (!pPipe || (pPipe->m_Thread != pShop->m_ThreadNumber))
						continue;
					if (pPipe->m_Type != 7) // 7 - труба обвязки КЦ
						continue;
					if (pPipe->m_NodeStart == pStartNode->m_ID)
						ShopStartNodes.push_back(pPipe->m_NodeEnd);
					if (pPipe->m_NodeEnd == pStartNode->m_ID)
						ShopStartNodes.push_back(pPipe->m_NodeStart);
				}
			}

			// EndNode
			{
				list<int> Edges;
				pEndNode->CollectEdges(Edges);
				for (list<int>::iterator j = Edges.begin(); j != Edges.end(); j++)
				{
					BObject *pObject = pModel->GetObject(*j);
					if (!pObject)
						continue;
					BPipe *pPipe = dynamic_cast<BPipe*>(pObject);
					if (!pPipe || (pPipe->m_Thread != pShop->m_ThreadNumber))
						continue;
					if (pPipe->m_Type != 7) // 7 - труба обвязки КЦ
						continue;
					if (pPipe->m_NodeStart == pEndNode->m_ID)
						ShopEndNodes.push_back(pPipe->m_NodeEnd);
					if (pPipe->m_NodeEnd == pEndNode->m_ID)
						ShopEndNodes.push_back(pPipe->m_NodeStart);
				}
			}

			// Поиск входных и выходных узлов КЦ, включая объединения на трубах обвязки КЦ
			RShopsGroup *pGroup = NULL;
			for (map <RShopsGroup*, RShopNodes>::iterator j = Groups.begin(); j != Groups.end(); j++)
			{	
				RShopNodes &Nodes = j->second;
				bool bStartFounded = false;
				for (list <int>::iterator k = Nodes.m_NodesStart.begin(); k != Nodes.m_NodesStart.end(); k++)
				{
					int NodeID = *k;
					for (list <int>::iterator l = ShopStartNodes.begin(); l != ShopStartNodes.end(); l++)
					{
						if (NodeID == *l)
						{
							bStartFounded = true;
							break;
						}
					}
					if (bStartFounded)
						break;
				}

				bool bEndFounded = false;
				for (list <int>::iterator k = Nodes.m_NodesEnd.begin(); k != Nodes.m_NodesEnd.end(); k++)
				{
					int NodeID = *k;
					for (list <int>::iterator l = ShopEndNodes.begin(); l != ShopEndNodes.end(); l++)
					{
						if (NodeID == *l)
						{
							bEndFounded = true;
							break;
						}
					}
					if (bEndFounded)
						break;
				}

				if (bStartFounded && bEndFounded)
				{
					pGroup = j->first;
					break;
				}
			}
			if (!pGroup)
			{
				pGroup = new RShopsGroup;
				pGroup->m_ID = ++m_MaxID;
				Groups[pGroup] = RShopNodes(ShopStartNodes, ShopEndNodes);
			}
			pGroup->AddShop(pShop);
			pGroup->m_Emin = max(pGroup->m_Emin, pShop->m_Emin);
			pGroup->m_Emax = min(pGroup->m_Emax, pShop->m_Emax);

			pGroup->m_dPin_max = max(pGroup->m_dPin_max, pShop->m_dPin);
			pGroup->m_dPout_max = max(pGroup->m_dPout_max, pShop->m_dPout);

			pGroup->m_dPin_min = min(pGroup->m_dPin_min, pShop->m_dPin);
			pGroup->m_dPout_min = min(pGroup->m_dPout_min, pShop->m_dPout);

			pShop->m_pGroup = pGroup;
		}

		for (map <RShopsGroup*, RShopNodes>::iterator i = Groups.begin(); i != Groups.end(); i++)
		{
			RShopsGroup *pGroup = i->first;
			pGroup->m_NodeStart = (*i->second.m_NodesStart.begin());
			pGroup->m_NodeEnd = (*i->second.m_NodesEnd.begin());
			pModel->AddObject(pGroup);
			AddEdge(pGroup);
			pGroup->PostAdd();
		}

/*		for (vector <RShopsGroup*>::iterator i = pModel->m_ParallelShops.begin(); i != pModel->m_ParallelShops.end(); i++)
		{
			RShopsGroup *pGroup = *i;
			string s = pGroup->m_SID;
			s += ". Цеха:";
			for (vector <BShop*>::iterator j = pGroup->m_pShops.begin(); j != pGroup->m_pShops.end(); j++)
			{
				s += itos((*j)->m_ShopNumber);
				s += " ";
			}
			DoLogForced(s);
		}	
*/

		return;
	}

	//// Формирование групп КЦ, имеющих общий вход и общий выход (без проверки объединения на трубах обвязки КЦ)
	//{
	//	// Формирование групп параллельных КЦ	
	//	struct RGroupNodes
	//	{
	//		RGroupNodes(void){}
	//		RGroupNodes(double NodeStart, double NodeEnd)
	//		{
	//			Start = NodeStart;
	//			End = NodeEnd;
	//		}
	//		void operator = (const RGroupNodes& Nodes)
	//		{
	//			Start = Nodes.Start;
	//			End = Nodes.End;
	//		}
	//		int Start;
	//		int End;
	//	};
	//	map <RShopsGroup*, RGroupNodes> Groups;

	//	for (vector <BObject*>::iterator i = pModel->m_Shops.begin(); i != pModel->m_Shops.end(); i++)
	//	{
	//		BShop *pShop = dynamic_cast<BShop*>(*i);
	//		assert(pShop);

	//		RShopsGroup *pGroup = NULL;
	//		for (map <RShopsGroup*, RGroupNodes>::iterator j = Groups.begin(); j != Groups.end(); j++)
	//		{
	//			RGroupNodes &Nodes = j->second;
	//			if ( (Nodes.Start == pShop->m_NodeStart) &&
	//				 (Nodes.End == pShop->m_NodeEnd)
	//				 )
	//			{
	//				pGroup = j->first;
	//				break;
	//			}
	//		}
	//		if (!pGroup)
	//		{
	//			pGroup = new RShopsGroup;
	//			Groups[pGroup] = RGroupNodes(pShop->m_NodeStart, pShop->m_NodeEnd);
	//		}
	//		pGroup->AddShop(pShop);
	//		pShop->m_pGroup = pGroup;
	//	}

	//	for (map <RShopsGroup*, RGroupNodes>::iterator i = Groups.begin(); i != Groups.end(); i++)
	//	{
	//		pModel->m_ParallelShops.push_back(i->first);
	//	}
	//}
}

}