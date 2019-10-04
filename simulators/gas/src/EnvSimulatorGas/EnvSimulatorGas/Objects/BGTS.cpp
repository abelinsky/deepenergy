#include "pch.h"
#include "BGTS.h"

namespace Objects {

BGTS::BGTS(void)
{
	m_kNmax = 1.1;
	m_bControlKcharge = true;
	m_TairAdd = 5;
	m_TAVO = 2;
	m_AVOCalc = 3;
	m_Pdrift = 0.1;
	m_Qvalidity = 0.1;
	m_Qdrift = 0.1;
	m_bControlKud = true;
	m_OptimizationCriteria	= 0;
	m_PipesCollapse = true;
	m_bIntershopsIgnore = true;
	m_GroupGRS = 1;
	m_nPointsMax = 16;
	m_FormulasType = 0;
	m_bKvaziDisable = false;
}

BGTS::~BGTS(void)
{
	GetModel()->m_pGTS = NULL;
}

void BGTS::LoadData(istream &in)
{
	in >> m_kNmax;
	in >> m_bControlKcharge;
	in >> m_TairAdd;
	in >> m_TAVO;
	in >> m_AVOCalc;
	in >> m_Pdrift;
	in >> m_Qvalidity;
	in >> m_Qdrift;
	in >> m_bControlKud;
	in >> m_OptimizationCriteria;
	in >> m_PipesCollapse;
	in >> m_bIntershopsIgnore;
	in >> m_GroupGRS;
	in >> m_nPointsMax;
	in >> m_FormulasType;
	in >> m_bKvaziDisable;
}

void BGTS::PostAdd()
{
	GetModel()->m_pGTS = this;
}

void BGTS::PostErased()
{
	GetModel()->m_pGTS = NULL;
}

void BGTS::PrintExportData(ostream &out)
{
	bool bControlKcharge = m_bControlKcharge;
	bool bControlKud = m_bControlKud;

	//if (!gData.m_bControlRestrictions)
	//{
	//	// снятие ограничений
	//	bControlKcharge = false;
	//	bControlKud = false;
	//}

	out << 
		m_kNmax << " " <<
		bControlKcharge << " " <<
		m_TairAdd << " " <<
		m_TAVO << " " <<
		m_AVOCalc << " " <<
		m_Pdrift << " " <<
		m_Qvalidity << " " <<
		m_Qdrift << " " <<
		bControlKud << " " <<
		m_OptimizationCriteria << " " <<
		m_PipesCollapse << " " <<
		m_bIntershopsIgnore << " " <<
		m_GroupGRS << " " <<
		m_nPointsMax << " " <<
		m_FormulasType << " " <<
		m_bKvaziDisable << " " <<
	endl;
}

}