#include "pch.h"
#include "BValve.h"

namespace Objects {

BValve::BValve(void)
{
	ClearResults();
}

BValve::~BValve(void)
{
}

void BValve::ClearResults()
{
	BObject::ClearResults();
	m_rDirection = 1;
}

int BValve::GetMatrixID()
{
	return 0;
}

void BValve::PostAdd()
{
	GetModel()->m_Valves.push_back(this);
}

void BValve::PostErased()
{
	vector <BObject*>::iterator i = find(GetModel()->m_Valves.begin(), GetModel()->m_Valves.end(), this);
	if (i != GetModel()->m_Valves.end())
	{
		GetModel()->m_Valves.erase(i);
	}
}

void BValve::ImportResults(istream &in)
{
	BObject::ImportResults(in);
	in >> m_rDirection;
}

void BValve::ExportResults(ostream &out)
{
	BObject::ExportResults(out);
	out << " " <<
		m_rDirection;
}

}