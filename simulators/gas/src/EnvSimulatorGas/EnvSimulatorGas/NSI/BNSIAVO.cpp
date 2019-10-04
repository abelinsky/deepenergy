#include "pch.h"
#include "BNSIAVO.h"

namespace NSI {

BNSIAVO::BNSIAVO(void)
{
	m_PipesCount = 0;
	m_StepsCount = 0;
	m_VentCount = 0;
	m_kFinning = 0.;
	m_PipesLength = 0.;
	m_Sout = 0.;
	m_Sin = 0.;
	m_Scutset = 0.;
	m_kTaper = 0.;
	m_C = 0.;
	m_QVent = 0.;
	m_l = 0.;
	m_h = 0.;
	m_w = 0.;
	m_k = 0.;
	m_N = 30;
}

BNSIAVO::~BNSIAVO(void)
{
}

bool BNSIAVO::CheckLoadedData(string& Error)
{
	return true;
}

void BNSIAVO::LoadData(istream &in)
{
	string s;
	in >> m_ID;
	in >> m_Name;
	getline(in, s);
	in >> m_PipesCount;
	in >> m_StepsCount;
	in >> m_VentCount;
	in >> m_kFinning;
	in >> m_PipesLength;
	in >> m_Sout;
	in >> m_Sin;
	in >> m_Scutset;
	in >> m_kTaper;
	in >> m_C;
	in >> m_QVent;
	in >> m_l;
	in >> m_h;
	in >> m_w;
	in >> m_k;
	if (!eol(in))
		in >> m_N;
}

void BNSIAVO::PrintExportData(ostream &out)
{
	out <<		
		m_ID << " " << 
		m_Name <<
	endl;

	out <<		
		m_PipesCount << " " << 
		m_StepsCount << " " << 
		m_VentCount << " " << 
		m_kFinning << " " << 
		m_PipesLength << " " << 
		m_Sout << " " << 
		m_Sin << " " << 
		m_Scutset << " " << 
		m_kTaper << " " << 
		m_C << " " << 
		m_QVent << " " << 
		m_l << " " << 
		m_h << " " << 
		m_w << " " << 
		m_k << " " <<
		m_N <<
	endl;
}

}