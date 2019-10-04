#include "pch.h"
#include "BPipe.h"

namespace Objects {

BPipe::BPipe(void)
{
	m_Type = 0;
	m_Thread = 0;
	m_Kef = 0.95;
	m_Kto = 1.3;
	m_T = 1.;
	m_Pmin = 0.;
	m_Pmax = 0.;
	m_d = 0.;
	m_D = 0.;
	m_L = 0.;
	m_k = 0.;
	m_dh = 0.;
	ClearResults();
}

BPipe::~BPipe(void)
{
}

void BPipe::ClearResults()
{
	BObject::ClearResults();
	m_rVin = 0.;
	m_rVout = 0.;
	m_rQv = 0.;
	m_rDirection = 1;
}

int BPipe::GetMatrixID()
{
	return 1;
}

bool BPipe::CheckLoadedData(string& Error)
{
	bool bSuccess = true;
	if (m_Kef == 0)
	{
		string s;
		s = (boost::format("The coefficient of hydraulic efficiency for pipe %d is not set\n") % m_ID).str();
		Error += s;
		bSuccess = false;
	}

	if (m_Kto == 0)
	{
		string s;
		s = (boost::format("The heat transfer coefficient for pipe %d is not set\n") % m_ID).str();
		Error += s;
		bSuccess = false;
	}

	if (m_Pmin == 0)
	{
		string s;
		s = (boost::format("The Pmin parameter for pipe %d is not set\n") % m_ID).str();
		Error += s;
		bSuccess = false;
	}

	if (m_Pmax == 0)
	{
		string s;
		s = (boost::format("The Pmax parameter for pipe %d is not set\n") % m_ID).str();
		Error += s;
		bSuccess = false;
	}

	if (m_d == 0)
	{
		string s;
		s = (boost::format("The inner diameter for pipe %d is not set\n") % m_ID).str();
		Error += s;
		bSuccess = false;
	}

	if (m_D == 0)
	{
		string s;
		s = (boost::format("The outer diameter for pipe %d is not set\n") % m_ID).str();
		Error += s;
		bSuccess = false;
	}

	if (m_L == 0)
	{
		string s;
		s = (boost::format("The length for pipe %d is not set\n") % m_ID).str();
		Error += s;
		bSuccess = false;
	}

	if (m_k == 0)
	{
		string s;
		s = (boost::format("The coefficient of roughness for pipe %d is not set\n") % m_ID).str();
		Error += s;
		bSuccess = false;
	}

	return bSuccess;
}

void BPipe::PostAdd()
{
	GetModel()->m_Pipes.push_back(this);
}

void BPipe::PostErased()
{
	vector <BObject*>::iterator i = find(GetModel()->m_Pipes.begin(), GetModel()->m_Pipes.end(), this);
	if (i != GetModel()->m_Pipes.end())
	{
		GetModel()->m_Pipes.erase(i);
	}
}

void BPipe::LoadData(istream &in)
{
	in >> m_Type;
	in >> m_Thread;
	in >> m_Kef;
	in >> m_Kto;
	in >> m_T;
	in >> m_Pmin;
	in >> m_Pmax;
	in >> m_d;
	in >> m_D;
	in >> m_L;
	in >> m_k;
	in >> m_dh;
}

void BPipe::PrintExportData(ostream &out)
{
	double Pmin = m_Pmin;
	double Pmax = m_Pmax;
	if (!gData.m_bControlRestrictions)
	{
		// снятие ограничений по давлениям
		Pmin = 5;
		Pmax *= 3;
	}

	double Kef = m_Kef*gData.m_kKeff;

	out <<
		m_ID << " " <<
		m_Type << " " <<
		m_Thread << " " <<
		Kef << " " <<
		m_Kto << " " <<
		m_T << " " <<
		Pmin << " " <<
		Pmax << " " <<
		m_d << " " <<
		m_D << " " <<
		m_L << " " <<
		m_k << " " <<
		m_dh <<
	endl;
}

void BPipe::ImportResults(istream &in)
{
	BObject::ImportResults(in);
	in >> m_rVin;
	in >> m_rVout;
	in >> m_rQv;	
	in >> m_rDirection;
}

void BPipe::ExportResults(ostream &out)
{
	BObject::ExportResults(out);
	out << " " <<
		m_rVin << " " <<
		m_rVout << " " <<
		m_rQv << " " <<
		m_rDirection;
}

bool BPipe::PrintInitData(ostream &out, bool bOut)
{
	if(bOut)
	{
		out <<
			m_rPout << " " <<
			m_rTout << " " <<
			m_rRo_out << " " <<
			m_rHout << " " <<
			"0.00" << " " <<
			"0.00" <<
		endl;
	}
	else
	{
		out <<
			m_rPin << " " <<
			m_rTin << " " <<
			m_rRo_in << " " <<
			m_rHin << " " <<
			"0.00" << " " <<
			"0.00" <<
		endl;
	}
	return true;
}

bool BPipe::GetPminMax(double& Pmin, double& Pmax)
{
	Pmin = m_Pmin;
	Pmax = m_Pmax;
	return true;
}

double Z(double paP, double kT, double suPl, double CO2, double N2)
{
	// 0 - ОНТП-85, 1 - СТО НТП 2006

	int FType = 1;

	double Ppr=paP/(29.5847e5*(0.05993*(26.831-suPl)+(CO2-0.392*N2)*0.01));
	double Tpr=kT/(88.25*(1.7591*(0.56364+suPl)-(CO2+1.681*N2)*0.01));
	if(FType != 0)
	{
		if(FType == 1)
		{
			double A1=-0.39+2.03/Tpr-3.16/(Tpr*Tpr)+1.09/(Tpr*Tpr*Tpr);
			double A2=0.0423-0.1812/Tpr+0.2124/(Tpr*Tpr);
			double z=1+A1*Ppr+A2*Ppr*Ppr;
			return z; //  НТП
		}
	}
	double z=1.-0.0241*Ppr/(1-1.68*Tpr+0.78*Tpr*Tpr+0.0107*Tpr*Tpr*Tpr);
	return z; //  ОНТП
}

void BPipe::SummA(double *pA, OptEnums::TypeA type)
{
	if (!m_bCalculated)
		return;

	const double c = 3.912*1e-2;
	switch (type)
	{
	case OptEnums::TypeA::A_ttr:
		{
			(*pA) += m_L*fabs(m_rQin);
			break;
		}
	case OptEnums::TypeA::A_ettr:
		{
			(*pA) += c*(m_rPin*m_rPin-m_rPout*m_rPout)*fabs(m_rQin); // формула 9.20 расчета ЭТТР ЛУ, методика энергоаудита ГТС (СТО Газпром 2.120-114-2007)
			break;
		}
	case OptEnums::TypeA::A_ottr:
		{
			
			//(*pA) += c*log(m_rPin/m_rPout)*fabs(m_rQin);
			double z1 = Z(m_rPin*98066.5/*[Па]*/, m_rTin+273.15, m_rRo_in, 0, 0);
			double z2 = Z(m_rPout*98066.5/*[Па]*/, m_rTout+273.15, m_rRo_out, 0, 0);
			double Za = (z1+z2)/2;
			double Ta = (m_rTin+m_rTout)/2+273.15;
			(*pA) += Za*Ta*log(m_rPin/m_rPout)*fabs(m_rQin);
			break;
		}
	default:
		{
			assert(FALSE);
		}
	};
}

}