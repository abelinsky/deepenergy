#include "pch.h"
#include "BObject.h"

namespace Objects {

BObject::BObject(void)
{
	m_bProcessed = false;
	m_ID = 0;
	m_NodeStart = -1;
	m_NodeEnd = -1;
	m_pMap = NULL;
	ClearResults();
}

void BObject::ClearResults()
{
	m_rPin = 0.;
	m_rTin = 0.;
	m_rRo_in = 0.;
	m_rHin = 0.;
	m_rQin = 0.;
	m_rPout = 0.;
	m_rTout = 0.;
	m_rRo_out = 0.;
	m_rHout = 0.;
	m_rQout = 0.;
	m_bCalculated = false;
	m_bPostCalculated = false;
	m_CalculatedEdgesCount = 0;
}

BObject::~BObject(void)
{
}

void BObject::F_Count(double *pCounter, OBJDPARAM lpParam)
{
	(*pCounter) += (*lpParam)(this);
}

void BObject::I_Count(int *pCounter, OBJIPARAM lpParam)
{
	(*pCounter) += (*lpParam)(this);
}

bool BObject::CheckLoadedData(string& Error)
{
	return true;
}

int BObject::GetMatrixID()
{
	return -1;
}

void BObject::ImportResults(istream &in)
{
	double d[10];
	for(int i = 0; i<10; i++)
	{
		in >> d[i];
	}

	m_rPin = d[0];
	m_rTin = d[1];
	m_rRo_in = d[2];
	m_rHin = d[3];
	m_rQin = d[4];
	m_rPout = d[5];
	m_rTout = d[6];
	m_rRo_out = d[7];
	m_rHout = d[8];
	m_rQout = d[9];

	CObjectsModel *pModel = &gData.m_Model;
	double Restrictions = 0;
	CNode *pStartNode = pModel->m_Connections.GetNode(m_NodeStart);
	CNode *pEndNode = pModel->m_Connections.GetNode(m_NodeEnd);
	if (pStartNode)
	{
		pStartNode->m_rP = m_rPin;
		pStartNode->m_rT = m_rTin;

		Restrictions += max(0., pStartNode->m_rP-pStartNode->m_Pmax);
		Restrictions += max(0., pStartNode->m_Pmin-pStartNode->m_rP);
		
	}
	
	if (pEndNode)
	{
		pEndNode->m_rP = m_rPout;
		pEndNode->m_rT = m_rTout;

		Restrictions += max(0., pEndNode->m_rP-pEndNode->m_Pmax);
		Restrictions += max(0., pEndNode->m_Pmin-pEndNode->m_rP);
	}

	pModel->m_RestrictionsP += Restrictions;
}

bool BObject::CanExport()
{
	return (GetMatrixID() >= 0);
}

void BObject::ExportResults(ostream &out)
{
	out <<
		m_ID << " " <<
		m_rPin << " " <<
		m_rTin << " " <<
		m_rRo_in << " " <<
		m_rHin << " " <<
		m_rQin << " " <<
		m_rPout << " " <<
		m_rTout << " " <<
		m_rRo_out << " " <<
		m_rHout << " " <<
		m_rQout;
}

bool BObject::OBJCMP(BObject *pObject1, BObject *pObject2)
{
	return pObject1->GetName()<pObject2->GetName();
}

bool BObject::GetPminMax(double& Pmin, double& Pmax)
{
	return false;
}

void BObject::SetCalculated(bool bCalculated)
{
	m_bCalculated = bCalculated;
	m_CalculatedEdgesCount = bCalculated?1:0;
}

void BObject::InitForExport()
{
	SetCalculated(false);
	m_bPostCalculated = false;
}

void BObject::PostCalculate(bool bPostCalculateChilds)
{	
	CheckResults();
	m_bPostCalculated = true;
}

double BObject::GetPOutMax()
{
	double Pmax = 0;
	CNode *pNode = GetModel()->m_Connections.GetNode(m_NodeEnd);
	if (pNode)
	{
		Pmax = pNode->m_Pmax;
	}
	return Pmax;
}

}