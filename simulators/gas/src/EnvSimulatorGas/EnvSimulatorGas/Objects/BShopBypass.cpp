#include "pch.h"
#include "BShopBypass.h"
#include "BShop.h"

namespace Objects {

BShopBypass::BShopBypass(void)
{
	m_Number = 0;
	m_Type = 0;
	m_ConnectionType = 0;
	m_DWhole = 0.;
	m_d = 0.;
//	m_oParam = 0.;
	m_k = 0.;
}

BShopBypass::~BShopBypass(void)
{
}

void BShopBypass::PostAdd()
{
	assert(m_pShop);
	m_pShop->m_Bypasses.push_back(this);
}

void BShopBypass::PostErased()
{
	vector <BShopBypass*>::iterator i = find(m_pShop->m_Bypasses.begin(), m_pShop->m_Bypasses.end(), this);
	if (i != m_pShop->m_Bypasses.end())
	{
		m_pShop->m_Bypasses.erase(i);
	}
}

bool BShopBypass::CheckLoadedData(string& Error)
{
	bool bSuccess = true;
	if (m_DWhole == 0.)
	{
		string s;
		//s = string_format("У крана № %d не задан внешний диаметр.\n", m_Number);
		s = (boost::format("Outer diameter is not set for valve %d") % m_Number).str();
		Error += s;
		bSuccess = false;
	}

	if (m_d == 0.)
	{
		string s;
		// s = string_format("У крана № %d не задан внутренний диаметр.\n", m_Number);
		s = (boost::format("Inner diameter is not set for valve %d") % m_Number).str();
		Error += s;
		bSuccess = false;
	}

	if (m_k == 0.)
	{
		string s;
		// s = string_format("У крана № %d не задан коэфф.сопротивления.\n", m_Number);
		s = (boost::format("Resistance coefficient is not set for valve %d") % m_Number).str();
		Error += s;
		bSuccess = false;
	}

	return bSuccess;
}

void BShopBypass::LoadData(istream& in)
{
	in >> m_Number;
	in >> m_Type;
	in >> m_ConnectionType;
	in >> m_DWhole;
	in >> m_d;
//	in >> m_oParam;
	in >> m_k;
}

void BShopBypass::PrintExportData(ostream &out)
{
	out <<
		m_Number << " " <<
		m_Type << " " <<
		m_ConnectionType << " " <<
		m_DWhole << " " <<
		m_d << " " <<
		m_k <<
	endl;
}

}