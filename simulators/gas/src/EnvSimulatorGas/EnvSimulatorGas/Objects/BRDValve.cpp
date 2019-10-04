#include "pch.h"
#include "BRDValve.h"

namespace Objects {

BRDValve::BRDValve(void)
{
	m_Type = 0;
	m_Pinmin = 0.;
	m_Poutmax = 0.;
	m_Pset = 0.;
	m_DWhole = 0.;
	m_d = 0.;
	m_k = 0.;
	ClearResults();
}

BRDValve::~BRDValve(void)
{
}

void BRDValve::ClearResults()
{
	BValve::ClearResults();
	m_rd = 0.;
	m_rk = 0.;
}

int BRDValve::GetMatrixID()
{
	return 3;
}

void BRDValve::PostAdd()
{
	GetModel()->m_RDValves.push_back(this);
}

void BRDValve::PostErased()
{
	vector <BObject*>::iterator i = find(GetModel()->m_RDValves.begin(), GetModel()->m_RDValves.end(), this);
	if (i != GetModel()->m_RDValves.end())
	{
		GetModel()->m_RDValves.erase(i);
	}
}

bool BRDValve::CheckLoadedData(string& Error)
{
	bool bSuccess = true;
	if (m_Pinmin == 0)
	{
		string s;
		s = (boost::format("The Pinmin parameter for valve ¹ %d is not set") % m_ID).str();
		Error += s;
		bSuccess = false;
	}

	if (m_Poutmax == 0)
	{
		string s;
		s = (boost::format("The Poutmax parameter for valve ¹ %d is not set") % m_ID).str();
		Error += s;
		bSuccess = false;
	}

	if (m_DWhole == 0)
	{
		string s;
		s = (boost::format("The diameter when fully open parameter for valve ¹ %d is not set") % m_ID).str();
		Error += s;
		bSuccess = false;
	}

	if (m_d == 0)
	{
		string s;
		s = (boost::format("The passage diameter parameter for valve ¹ %d is not set") % m_ID).str();
		Error += s;
		bSuccess = false;
	}

	if (m_k == 0)
	{
		string s;
		s = (boost::format("The coefficient of local resistances for valve ¹ %d is not set") % m_ID).str();
		Error += s;
		bSuccess = false;
	}

	return bSuccess;
}

void BRDValve::LoadData(istream& in)
{
	in >> m_Type;
	in >> m_Pinmin;
	in >> m_Poutmax;
	in >> m_Pset;
	in >> m_DWhole;
	in >> m_d;
	in >> m_k;
}

void BRDValve::PrintExportData(ostream &out)
{
	out <<
		m_ID << " " <<
		m_Type << " " <<
		m_Pinmin << " " <<
		m_Poutmax << " " <<
		m_Pset << " " <<
		m_DWhole << " " <<
		m_d << " " <<
		m_k <<
	endl;
}

void BRDValve::ImportAdaptation(istream &in)
{
	double d[2];
	for(int i = 0; i<2; i++)
	{
		in >> d[i];
	}
	if (m_Type == 0)
	{
		m_rd = d[0];
		m_rk = d[1];
	}
}

void BRDValve::ExportAdaptation(ostream &out)
{
	out <<
		m_ID << " " <<
		m_rd << " " <<
		m_rk;
}

}