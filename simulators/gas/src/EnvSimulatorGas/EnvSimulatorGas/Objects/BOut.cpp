#include "pch.h"
#include "BOut.h"

namespace Objects {

	BOut::BOut(void)
	{
		m_Node = 0;
		m_P = 0.;
		m_Q = 0.;
		m_Type = 0;
		m_Pmin = 0;
		m_nThread = 0;
		m_pMap = &(GetModel()->m_InOutMap);
		ClearResults();
	}

	BOut::~BOut(void)
	{
	}

	void BOut::ClearResults()
	{
		BObject::ClearResults();
		m_rP = 0.;
		m_rT = 0.;
		m_rRo = 0.;
		m_rH = 0.;
		m_rQ = 0.;
		m_rCO2 = 0.;
		m_rN2 = 0.;
	}

	bool BOut::CheckLoadedData(string& Error)
	{
		bool bSuccess = true;
		if (m_P == 0. && m_Q == 0.)
		{
			string s;
			s = (boost::format("There is neither P, neither Q set for consumer %d\n") % m_ID).str();
			Error += s;
			bSuccess = false;
		}
		return bSuccess;
	}

	void BOut::PostAdd()
	{
		GetModel()->m_Outs.push_back(this);
	}

	void BOut::PostErased()
	{
		vector <BObject*>::iterator i = find(GetModel()->m_Outs.begin(), GetModel()->m_Outs.end(), this);
		if (i != GetModel()->m_Outs.end())
		{
			GetModel()->m_Outs.erase(i);
		}
	}

	void BOut::PrintExportData(ostream &out)
	{
		out <<
			m_Node;

		// Заданы избыточные параметры?
		bool bSurplusParams = (m_Q && m_P);

		if((m_Q == 0) || bSurplusParams) // для оптимизации в Calc передаем только P
		{
			//out	<< " " << ftos(m_Q);
			out	<< " 0.0";
		}
		else
		{
			out	<< " -" << ftos(m_Q, 8);
		}
		out	<< " " <<
			"0.0" << " " <<
			"0.0" << " " <<
			ftos(m_P) << " " <<
			"0.0" << " " <<
			"0.0" << " " <<
			"0.0" << " " <<
			m_Type << " " << 
			m_ID <<	 " " << 
			ftos(m_Pmin) <<	 " " << 
			m_nThread <<
		endl;
	}

	void BOut::ExportResults(ostream &out)
	{
		out <<
			m_ID << " " <<
			m_Node << " " <<
			m_rP << " " <<
			m_rT << " " <<
			m_rRo << " " <<
			m_rH << " " <<
			m_rQ << " " <<
			m_rCO2 << " " <<
			m_rN2;
	}

	bool BOut::PrintInitData(ostream &out, bool bOut)
	{
		out <<
			m_rP << " " <<
			m_rT << " " <<
			m_rRo << " " <<
			m_rH << " " <<
			m_rN2 << " " <<
			m_rCO2 <<
		endl;
		return true;
	}

	void BOut::ImportResults(istream &in)
	{
		double d[8];
		for(int i = 0; i<8; i++)
			in >> d[i];
		m_rP = d[1];
		m_rT = d[2];
		m_rRo = d[3];
		m_rH = d[4];
		m_rQ = d[5];
		m_rCO2 = d[6];
		m_rN2 = d[7];
	}

	void BOut::ResultsToObject()
	{
		m_P = m_rP;
		m_Q = fabs(m_rQ);
	}

	void BOut::SummA(double *pA, OptEnums::TypeA type)
	{
		if (!m_bCalculated)
			return;

		const double c = 0.03912;
		switch (type)
		{
		case OptEnums::TypeA::A_ttr:
			{
				break;
			}
		case OptEnums::TypeA::A_ettr:
			{
				(*pA) += c*m_rP*m_rP*fabs(m_rQ); // формула 9.6 расчета ЭТТР ЛУ, методика энергоаудита ГТС (СТО Газпром 2.120-114-2007)
				break;
			}
		case OptEnums::TypeA::A_ottr:
			{
				(*pA) += log(m_rP)*fabs(m_rQ);
				break;
			}
		default:
			{
				assert(FALSE);
			}
		};
	}

	void BOut::ExportDynamicsData()
	{
		assert(m_pMap);

		DMapFile &MapFile = *m_pMap;
		MapFile << -float(fabs(m_rQ));
		MapFile << float(m_rP);
		MapFile << float(m_rT);
		MapFile << float(m_rRo); 
	}

}