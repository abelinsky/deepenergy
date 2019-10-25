#include "pch.h"
#include "BIn.h"
#include "BOut.h"

namespace Objects {

	bool BInOut::LoadData(istream &in, string& Error)
	{
		int nInOutCount;
		in >> nInOutCount;
		string s;
		getline(in, s);
	
		for (int i = 0; i<nInOutCount; i++)
		{
			int NodeID;
			double Q;
			double T;
			double Ro;
			double P;
			double N2;
			double C02;
			double H;
			int Type;
			int ObjectID;
			double Pmin;
			int nThread;

			in >> NodeID;
			in >> Q;
			in >> T;
			in >> Ro;
			in >> P;
			in >> N2;
			in >> C02;
			in >> H;
			in >> Type;
			if (!eol(in))
				in >> ObjectID;
			if (!eol(in))
				in >> Pmin;
			if (!eol(in))
				in >> nThread;

			if (Type == 10) // фиктивный отбор
				continue;

			CNode *pNode = GetModel()->m_Connections.GetNode(NodeID);
			if (!pNode)
			{
				Error = (boost::format("Node %d not set") % NodeID).str();
				return false;
			}

			if (!GetModel()->GetObject(ObjectID))
			{
				if (Ro>0 || N2>0 || C02>0 || H>0) // Поставщик
				{
					BIn *pIn = new BIn;
					pIn->m_ID = ObjectID;
					GetModel()->AddObject(pIn);

					pIn->m_Node = NodeID;
					pIn->m_Q = Q;
					pIn->m_T = T;
					pIn->m_Ro = Ro;
					pIn->m_P = P;
					pIn->m_N2 = N2;
					pIn->m_C02 = C02;
					pIn->m_H = H;

					pNode->m_Ins.push_back(ObjectID);
				}
				else
				{
					BOut *pOut = new BOut;
					pOut->m_ID = ObjectID;
					GetModel()->AddObject(pOut);

					pOut->m_Node = NodeID;
					pOut->m_Q = fabs(Q);
					pOut->m_P = P;
					pOut->m_Type = Type;
					pOut->m_Pmin = Pmin;
					pOut->m_nThread = nThread;

					pNode->m_Outs.push_back(ObjectID);
				}
			}

			getline(in, s);
		}

		return true;
	}

	BIn::BIn(void)
	{
		m_Node = 0;
		m_P = 0.;
		m_Q = 0.;
		m_T = 0.;
		m_Ro = 0.;
		m_N2 = 0.;
		m_C02 = 0.;
		m_H = 0.;
		m_pMap = &(GetModel()->m_InOutMap);
		ClearResults();
	}

	BIn::~BIn(void)
	{
	}

	void BIn::ClearResults()
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

	bool BIn::CheckLoadedData(string& Error)
	{
		bool bSuccess = true;
		if (m_P == 0. && m_Q == 0.)
		{
			string s;
			s = (boost::format("There is neither P, neither Q set for supplier %d\n") % m_ID).str();
			Error += s;
			bSuccess = false;
		}
		if (m_Ro == 0.)
		{
			string s;
			s = (boost::format("Gas density is not set for supplier %d\n") % m_ID).str();
			Error += s;
			bSuccess = false;
		}
		return bSuccess;
	}

	void BIn::PostAdd()
	{
		GetModel()->m_Ins.push_back(this);
	}

	void BIn::PostErased()
	{
		vector <BObject*>::iterator i = find(GetModel()->m_Ins.begin(), GetModel()->m_Ins.end(), this);
		if (i != GetModel()->m_Ins.end())
		{
			GetModel()->m_Ins.erase(i);
		}
	}

	void BIn::PrintExportData(ostream &out)
	{
		// Заданы избыточные параметры?
		double Q = m_Q;
		double P = m_P;
		bool bSurplusParams = (m_Q && m_P);
		if (bSurplusParams)
			Q = 0;
		P *= gData.m_kP;

		out <<
			m_Node << " " <<
			ftos(Q, 8) << " " <<
			m_T << " " <<
			m_Ro << " " <<
			P << " " <<
			m_N2 << " " <<
			m_C02 << " " <<
			m_H << " " <<
			"0" << " " <<
			m_ID << " " << 0 <<
			endl;
	}

	void BIn::ExportResults(ostream &out)
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

	bool BIn::PrintInitData(ostream &out, bool bOut)
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

	void BIn::ImportResults(istream &in)
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

	void BIn::SummA(double *pA, OptEnums::TypeA type)
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
				(*pA) += fabs(c*m_rP*m_rP*m_rQ); // формула 9.5 расчета ЭТТР ЛУ, методика энергоаудита ГТС (СТО Газпром 2.120-114-2007)
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

	void BIn::ExportDynamicsData()
	{
		assert(m_pMap);

		DMapFile &MapFile = *m_pMap;
		MapFile << float(m_rQ);
		MapFile << float(m_rP);
		MapFile << float(m_rT);
		MapFile << float(m_rRo); // TODO check the necessity of multiplication 1.20445

		DoLogForced("Dynamics exported: Q = " + ftos(m_rQ) + ", P = " + ftos(m_rP) + ", T = " + ftos(m_rT) + ", Ro = " + ftos(m_rRo));
	}

}