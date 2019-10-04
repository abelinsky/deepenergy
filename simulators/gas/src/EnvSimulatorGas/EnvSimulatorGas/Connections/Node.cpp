#include "pch.h"
#include "Node.h"
#include "BObject.h"

namespace Connections {

CNode::CNode(void)
{
	CNode(0);
	m_Pmin = 0.;
	m_Pmax = 0.;
	m_rP = 0.;
	m_rT = 0.;
}

CNode::CNode(int ID)
{
	m_ID = ID;
	m_Pmin = 0.;
	m_Pmax = 0.;
	m_rP = 0.;
	m_rT = 0.;
}

CNode::~CNode(void)
{
}

void CNode::Clear()
{
	m_ID = 0;
	m_InEdges.clear();
	m_OutEdges.clear();
	m_Ins.clear();
	m_Outs.clear();
}

void CNode::AddEdgeIn(BObject *pObject)
{
	assert(pObject);
	if (!pObject)
		return;
	AddEdgeIn(pObject->m_ID);
	pObject->m_NodeEnd = m_ID;
}

void CNode::AddEdgeIn(int ID)
{
	m_InEdges.push_back(ID);
}

void CNode::AddEdgeOut(BObject *pObject)
{
	assert(pObject);
	if (!pObject)
		return;
	AddEdgeOut(pObject->m_ID);
	pObject->m_NodeStart = m_ID;
}

void CNode::AddEdgeOut(int ID)
{
	m_OutEdges.push_back(ID);
}

void CNode::Attach(CNode *pNode)
{
	pNode->Clear();
	pNode->m_ID = m_ID;
	pNode->m_InEdges.assign(m_InEdges.begin(), m_InEdges.end());
	pNode->m_OutEdges.assign(m_OutEdges.begin(), m_OutEdges.end());
	pNode->m_Ins.assign(m_Ins.begin(), m_Ins.end());
	pNode->m_Outs.assign(m_Outs.begin(), m_Outs.end());
	pNode->m_Pmin = m_Pmin;
	pNode->m_Pmax = m_Pmax;
}

void CNode::CollectEdges(list<int> &List)
{
	List.insert(List.end(), m_InEdges.begin(), m_InEdges.end());
	List.insert(List.end(), m_OutEdges.begin(), m_OutEdges.end());
	List.insert(List.end(), m_Ins.begin(), m_Ins.end());
	List.insert(List.end(), m_Outs.begin(), m_Outs.end());
}

bool CNode::EraseEdge(int ID)
{
	bool bResult = false;
	vector <int>::iterator i;
	i = find(m_InEdges.begin(), m_InEdges.end(), ID);
	if (i != m_InEdges.end())
	{
		m_InEdges.erase(i);
		bResult = true;
	}

	i = find(m_OutEdges.begin(), m_OutEdges.end(), ID);
	if (i != m_OutEdges.end())
	{
		m_OutEdges.erase(i);
		bResult = true;
	}

	return bResult;
}

void CNode::ExportInitData(ostream &out)
{
	out << m_ID << " ";

	for(vector <int>::iterator i = m_Ins.begin(); i != m_Ins.end(); i++)
	{
		BObject *pObject = GetModel()->GetObject(*i);
		assert(pObject);
		if(pObject->PrintInitData(out, true))
		{
			return;
		}
	}
	for(vector <int>::iterator i = m_Outs.begin(); i != m_Outs.end(); i++)
	{
		BObject *pObject = GetModel()->GetObject(*i);
		assert(pObject);
		if(pObject->PrintInitData(out, false))
		{
			return;
		}
	}

	for(vector <int>::iterator i = m_InEdges.begin(); i != m_InEdges.end(); i++)
	{
		BObject *pObject = GetModel()->GetObject(*i);
		assert(pObject);
		if(pObject->PrintInitData(out, true))
		{
			return;
		}
	}
	for(vector <int>::iterator i = m_OutEdges.begin(); i != m_OutEdges.end(); i++)
	{
		BObject *pObject = GetModel()->GetObject(*i);
		assert(pObject);
		if(pObject->PrintInitData(out, false))
		{
			return;
		}
	}

	out <<
		"0.00" << " " <<
		"0.00" << " " <<
		"0.00" << " " <<
		"0.00" << " " <<
		"0.00" << " " <<
		"0.00" <<
	endl;
}

void CNode::PostObjectsLoad()
{
	vector <int> Objects;
	Objects.insert(Objects.end(), m_InEdges.begin(), m_InEdges.end());
	Objects.insert(Objects.end(), m_OutEdges.begin(), m_OutEdges.end());

	for(vector <int>::iterator i = Objects.begin(); i != Objects.end(); i++)
	{
		BObject *pObject = GetModel()->GetObject(*i);
		assert(pObject);
		double Pmin = 0;
		double Pmax = 0;
		if (pObject->GetPminMax(Pmin, Pmax))
		{
			m_Pmin = m_Pmin ? max(m_Pmin, Pmin) : Pmin;
			m_Pmax = m_Pmax ? min(m_Pmax, Pmax) : Pmax;
		}
	}
}

}