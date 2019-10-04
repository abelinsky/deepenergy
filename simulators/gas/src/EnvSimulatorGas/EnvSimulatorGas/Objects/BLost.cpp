#include "pch.h"
#include "BLost.h"

namespace Objects {

BLost::BLost(void)
{
	m_dP = 0.;
	m_dT = 0.;
	m_dQ = 0.;
}

BLost::~BLost(void)
{
}

int BLost::GetMatrixID()
{
	return 4;
}

void BLost::PostAdd()
{
	GetModel()->m_Losts.push_back(this);
}

void BLost::PostErased()
{
	vector <BObject*>::iterator i = find(GetModel()->m_Losts.begin(), GetModel()->m_Losts.end(), this);
	if (i != GetModel()->m_Losts.end())
	{
		GetModel()->m_Losts.erase(i);
	}
}

void BLost::LoadData(istream &in)
{
	in >> m_dP;
	in >> m_dT;
	in >> m_dQ;
}

void BLost::PrintExportData(ostream &out)
{
	out << 
		m_ID << " " <<
		m_dP << " " <<
		m_dT << " " <<
		m_dQ <<
//		" 0" <<
		endl;
}

}