#include "pch.h"
#include "BShop.h"
#include "BShopGPA.h"
#include "BShopGPAGroup.h"
#include "BShopBypass.h"
#include "BShopObject.h"
#include "RShopsGroup.h"
#include "Objects.h"

namespace Objects {

	unordered_map <int, int> BShop::sLoadingMap; // допустимое количество "Всего ГПА в КЦ - количество резервных"

	BShop::BShop(void)
	{	
		m_ThreadNumber = 0;
		m_ShopNumber = 0;
		m_pGroup = NULL;
		m_kE = 1.;
		m_kK = 1.;
		m_kn = 1.;
		m_Qcost = 0.;
		m_Wcost = 0.;
		m_RDValvesCount = 0;
		m_dE = 1.;
		m_dP = 0.;
		m_dT = 0.;
		m_dQ = 0.;
		m_LostKind = 0;
		m_bFlowMode = false;

		m_Tair = 0.;
		m_Pair = 0.;
		m_Pinmin = 0.;
		m_Poutmax = 0.;
		m_Toutmax = 0.;
		m_dPin = 0.;
		m_dPout = 0.;
		m_nShopGPAs = 0;
		m_nWGroupsCount = 0;
		m_nShopGPAReserve = 0;
		m_AVOID = 0;
		m_nAVOCount = 0;
		m_nVentAVOCount = 0;
		m_AVOT_dt = 0.;
		m_Poutmin = 0.;
		m_Qmax = 0.;
		m_Qtg = 0.;
		m_Pset = 0.;
		m_Emax = 0.;
		m_Emin = 0.;
		m_CalcType = 0;
		m_bWShop = true;
		ClearResults();

		m_pGroupDisabled = new BShopGPAGroup;
		m_pGroupDisabled->m_ID = -1;

		m_pParams[OParam::O_E] = new RManagedParam(this, &m_dE, OParam::O_E);

		// допустимое количество "Всего ГПА в КЦ - количество резервных"
		// если в КЦ меньше 5 ГПА, то в резерве должен быть 1 ГПА
		for (int i = 1; i<=4; i++)
		{
			sLoadingMap[i] = 1;
		}
		// если в КЦ больше 5 ГПА, то в резерве должно быть 2 ГПА
		for (int i = 5; i<=25; i++)
		{
			sLoadingMap[i] = 2;
		}

		m_pMap = &(GetModel()->m_ShopMap);

	}

	BShop::~BShop(void)
	{
		ClearShop();
		delete m_pGroupDisabled;
	}

	void BShop::ClearResults()
	{
		BObject::ClearResults();
		for (unordered_map <int, BShopGPAGroup*>::iterator i = m_rWorkingGroups.begin();	i != m_rWorkingGroups.end(); i++)
		{
			delete i->second;
		}
		m_rWorkingGroups.clear();
	
		m_rCO2 = 0.;
		m_rN2 = 0.;

		m_rsE = 0;
		m_rsTng = 0;
		m_rsQtg = 0;
		m_rsQon = 0;
		m_rsW = 0;
		m_rsN = 0;
		m_rsNres = 0;
		m_rsQb = 0;
		m_rsAVOcount = 0;
		m_rsAVOVent = 0;
		m_rsEff = 0;
		m_A = 0;
		m_B = 0;
		m_rsL = 0;
		m_rsWAVO = 0;

		m_rsQtgCost = 0;
		m_rsWCost = 0;
		m_rsWAVOCost = 0;
	}

	int BShop::GetMatrixID()
	{
		return IsFlowMode()?4:2;
	}

	bool BShop::CanExport()
	{
		bool bCanExport = (BObject::CanExport() && !IsFlowMode());
		bCanExport &= !m_WorkingGroups.empty();
		return bCanExport;

		
		//bool bStateBool = true;
		//if (IsFlowMode() && (m_dE<=1))
		//{
		//	bStateBool = false;
		//}

		//if (!IsFlowMode() && m_WorkingGroups.empty())
		//{
		//	bStateBool = false;
		//}

		//bCanExport &= bStateBool;

		//return bCanExport;
	}

	void BShop::ClearShop()
	{
		for (unordered_map <int, BShopGPAGroup*>::iterator i = m_WorkingGroups.begin(); i != m_WorkingGroups.end(); i++)
		{
			delete i->second;
		}
		m_WorkingGroups.clear();
	
		for (vector <BShopGPA*>::iterator i = m_pAllGPAs.begin(); i != m_pAllGPAs.end(); i++)
		{
			delete *i;
		}
		m_pAllGPAs.clear();
	
		for (vector <BShopBypass*>::iterator i = m_Bypasses.begin(); i != m_Bypasses.end(); i++)
		{
			delete *i;
		}
		m_Bypasses.clear();
		m_pGroupDisabled->m_pGPAs.clear();

		for (unordered_map <int, BShopGPAGroup*>::iterator i = m_rWorkingGroups.begin();	i != m_rWorkingGroups.end(); i++)
		{
			delete i->second;
		}
		m_rWorkingGroups.clear();
	}

	bool BShop::AddGroup(BShopGPAGroup *pGroup, bool bResults)
	{
		unordered_map <int, BShopGPAGroup*> *pGroups = bResults ? &m_rWorkingGroups : &m_WorkingGroups;
		if (pGroups->find(pGroup->m_ID) == pGroups->end())
		{
			(*pGroups)[pGroup->m_ID] = pGroup;
			return true;
		}
		return false;
	}

	BShopGPAGroup* BShop::GetGroup(int GroupID, bool bResults)
	{
		unordered_map <int, BShopGPAGroup*> *pGroups = bResults ? &m_rWorkingGroups : &m_WorkingGroups;
		if (pGroups->find(GroupID) != pGroups->end())
			return (*pGroups)[GroupID];
		return NULL;
	}

	void BShop::AddChild(BShopObject *pObject)
	{
		pObject->m_pShop = this;
		pObject->PostAdd();
	}

	void BShop::PostAdd()
	{
		GetModel()->m_Shops.push_back(this);
	}

	void BShop::PostErased()
	{
		vector <BObject*>::iterator i = find(GetModel()->m_Shops.begin(), GetModel()->m_Shops.end(), this);
		if (i != GetModel()->m_Shops.end())
		{
			GetModel()->m_Shops.erase(i);
		}
	}

	void BShop::LoadData(istream &in)
	{
		if (IsFlowMode())
		{
			double Lost;
			in >> Lost;
			in >> m_dT;
			in >> m_dQ;
			in >> m_LostKind;
			in >> m_Emin;
			in >> m_Emax;
			switch (m_LostKind)
			{
			case 1:
				{
					m_dP = Lost;
					break;
				}
			case 2:
				{
					m_dE = Lost;
					break;
				}
			}
		}
		else
		{
			int nGPA = 0;
			string s;

			in >> m_KSName;
			in >> m_ThreadNumber;
			in >> m_ShopNumber;
			in >> m_kE; m_kE = 1.; // Больше не используется	
			in >> m_kK;
			in >> m_kn;
			in >> m_Qcost;
			in >> m_Wcost;
			in >> m_RDValvesCount;
			in >> m_dP;
			in >> m_dT;
			in >> m_dQ;
			getline(in, s);

			in >> m_Tair;
			in >> m_Pair;
			in >> m_Pinmin;
			in >> m_Poutmax;
			in >> m_Toutmax;
			in >> m_dPin;
			in >> m_dPout;
			in >> m_nShopGPAs;
			in >> m_nWGroupsCount;
			in >> m_nShopGPAReserve;
			in >> m_AVOID;
			in >> m_nAVOCount;
			in >> m_nVentAVOCount;
			in >> m_AVOT_dt;
			in >> m_Poutmin;
			in >> m_Qmax;
			in >> m_Qtg;
			in >> m_Pset;
			in >> m_Emax;
			in >> m_Emin;
			if (!eol(in))
				in >> m_CalcType;
			getline(in, s);

			m_Qmax = 112;

			//if (m_KSName == "КС_Верхнеказымская")
				//m_Qmax = 106;  // Для расчета 1045 на выход степ.сжатия 1,37 
			//if ((m_KSName == "КС_Приозерная") && (m_ShopNumber != 10))
				//m_Qmax = 107;
			//m_Emin = ;
			//m_Emax = ;
		
			//if (m_CalcType != 1)
				//m_CalcType = 2; // для КЦ с фиксированными схемами параметр не задавать

			int nRestGPA = m_nShopGPAs;

			// Далее в цикле по группам данного КЦ
			for (int i = 1; i<=m_nWGroupsCount; i++)
			{
				BShopGPAGroup *pGroup = new BShopGPAGroup;
				pGroup->m_ID = i;
				AddGroup(pGroup);
				in >> pGroup->m_nStages;
			
				// Далее в цикле по ступеням данной группы ГПА
				for (int j = 1; j<=pGroup->m_nStages; j++)
				{
					getline(in, s);
					BShopGPA *pShopGPA = new BShopGPA;
					pShopGPA->LoadData(in);
					pShopGPA->m_State = 1;
					AddChild(pShopGPA);
					m_GPAs[pShopGPA->m_Number] = pShopGPA;
					pGroup->AddShopGPA(pShopGPA);
					nRestGPA--;
					pShopGPA->m_SID = (boost::format("SHOP_%d_GPA_%d") % m_ID % pShopGPA->m_Number).str();
				}
			}

			// Далее в цикле по выключенным ГПА
			for (int i = 1; i<=nRestGPA; i++)
			{
				if (m_nWGroupsCount || i>1)
				{
					getline(in, s);
				}
				BShopGPA *pShopGPA = new BShopGPA;
				pShopGPA->LoadData(in);
				pShopGPA->m_State = 0;
				AddChild(pShopGPA);
				m_GPAs[pShopGPA->m_Number] = pShopGPA;
				m_pGroupDisabled->AddShopGPA(pShopGPA);
				// pShopGPA->m_SID = string_format("%s КЦ %d ГПА № %d", m_KSName, m_ShopNumber, pShopGPA->m_Number);
				pShopGPA->m_SID = (boost::format("SHOP_%d_GPA_%d") % m_ID % pShopGPA->m_Number).str();
			}

			// Далее в цикле по кранам байпасирования
			for (int i = 1; i<=m_RDValvesCount; i++)
			{
				getline(in, s);
				BShopBypass *pBypass = new BShopBypass;
				pBypass->LoadData(in);
				AddChild(pBypass);
			}
		}

		//m_Poutmax -= m_dPout;

		// m_Name = string_format("%s КЦ %d", m_KSName, m_ShopNumber);
		m_Name = (boost::format("%s Shop %d") % m_KSName % m_ShopNumber).str();
		m_SID = (boost::format("Shop%d") % m_ID).str(); 

		string_replace(m_Name, "_", " ");
	}

	bool BShop::CheckLoadedData(string &Error)
	{
		bool bSuccess = true;
		for (vector <BShopGPA*>::iterator i = m_pAllGPAs.begin(); i != m_pAllGPAs.end(); i++)
		{
			BShopGPA *pObject = *i;
			bSuccess &= pObject->CheckLoadedData(Error);
		}
		for (vector <BShopBypass*>::iterator i = m_Bypasses.begin(); i != m_Bypasses.end(); i++)
		{
			BShopBypass *pObject = *i;
			bSuccess &= pObject->CheckLoadedData(Error);
		}
		if (m_Emin < 1. || m_Emax <= 1.)
		{
			string s;
			// s = string_format("У КЦ \"%s\" не заданы минимально/максимально допустимые степени сжатия (Emin=%.2f, Emax=%.2f).\n", m_Name, m_Emin, m_Emax);
			s = (boost::format("Min and max compression ratio are not set for Shop \"%s\" (Emin=%.2f, Emax=%.2f).\n") % m_Name % m_Emin % m_Emax).str();
			Error += s;
			bSuccess = false;
		}
		return bSuccess;
	}

	bool BShop::IsFlowMode()
	{
		return m_bFlowMode;
	}

	void BShop::SetFlowMode(bool bFlowMode)
	{
		m_bFlowMode = bFlowMode;
		if (bFlowMode)
		{
			m_dE = m_rsE;
			m_dQ = m_rsQtg;
			m_dT = m_rTout-m_rTin;
			m_LostKind = 2;
		}
	}

	void BShop::PrintExportLosts(ostream& lost_ad, ostream& lost)
	{
		lost_ad << m_ID << " " << m_ShopNumber << " " << m_KSName << endl;
		lost << m_ID << " " <<
			((m_LostKind == 2)?m_dE:m_dP) << " " <<
			m_dT << " " <<
			m_dQ << " " <<
			m_LostKind << " " <<
			m_Emin << " " <<
			m_Emax <<
		endl;
	}

	void BShop::PrintExportData(ostream &out)
	{
		int nWGroupsCount = m_WorkingGroups.size();
		int nShopGPAs = m_pAllGPAs.size();
		int nShopGPAReserve = sLoadingMap[nShopGPAs]; //0; // можно задать количество резервных ГПА для оптимизационной задачи

		out << m_ID << endl;
		out <<
			m_KSName << " " <<
			m_ThreadNumber << " " <<
			m_ShopNumber << " " <<
			m_kE << " " <<
			m_kK << " " <<
			m_kn << " " <<
			m_Qcost << " " <<
			m_Wcost << " " <<
			m_RDValvesCount << " " <<
			m_dP << " " <<
			m_dT << " " <<
			m_dQ << 
		endl;

		double Pinmin = m_Pinmin;
		double Poutmax = m_Poutmax;
		if (!gData.m_bControlRestrictions)
		{
			// снятие ограничений по давлениям
			Pinmin = 5;
			Poutmax *= 3;
		}

		double Tset = m_AVOT_dt;
		Tset = m_pGroup->m_setTout;
		int AVOID = m_AVOID;
		//if (gData.m_TMode == OptEnums::TMode::T_Set)
			//AVOID = 0;

		out <<
			m_Tair << " " <<
			m_Pair << " " <<
			Pinmin << " " <<
			Poutmax << " " <<
			m_Toutmax << " " <<
			m_dPin << " " <<
			m_dPout << " " <<
			nShopGPAs << " " <<
			nWGroupsCount << " " <<
			nShopGPAReserve << " " <<
			AVOID << " " <<
			m_nAVOCount << " " <<
			m_nVentAVOCount << " " <<
			Tset << " " <<
			m_Poutmin << " " <<
			m_Qmax << " " <<
			m_Qtg << " " <<
			m_Pset << " " <<
			m_Emax << " " <<
			m_Emin << " " <<
			m_CalcType <<
			//"2" <<
		endl;

		// Далее в цикле по группам данного КЦ
		for (unordered_map <int, BShopGPAGroup*>::iterator i = m_WorkingGroups.begin(); i != m_WorkingGroups.end(); i++)
		{
			BShopGPAGroup *pGroup = i->second;
			int nStages = pGroup->m_pGPAs.size();
			out << nStages << endl;
			// Далее в цикле по ступеням данной группы ГПА
			for (vector <BShopGPA*>::iterator j = pGroup->m_pGPAs.begin(); j != pGroup->m_pGPAs.end(); j++)
			{
				BShopGPA *pShopGPA = *j;
				pShopGPA->PrintExportData(out);
			}
		}

		// Далее в цикле по выключенным ГПА
		for (vector <BShopGPA*>::iterator i = m_pGroupDisabled->m_pGPAs.begin(); i != m_pGroupDisabled->m_pGPAs.end(); i++)
		{
			BShopGPA *pShopGPA = *i;
			pShopGPA->PrintExportData(out);
		}

		// Далее в цикле по кранам байпасирования
		for (vector <BShopBypass*>::iterator i = m_Bypasses.begin(); i != m_Bypasses.end(); i++)
		{
			BShopBypass *pBypass = *i;
			pBypass->PrintExportData(out);
		}
	}

	void BShop::ImportResults(istream& in)
	{
		BObject::ImportResults(in);
		in >> m_rCO2;
		in >> m_rN2;

		m_rsQtg = m_rQin-m_rQout; // Расход топливного газа [млн.м3/сут]
		m_rsQon = m_rsQtg; // Расход газа на собственные нужды [млн.м3/сут]	

		// Расчет показателей энергоэффективности
		double c1 = 10.138;
		double P1 = m_rPin;
		double P2 = m_rPout;	
		double Ro = m_rRo_in;
		double T1 = m_rTin+273.15;
		double z = 1-((10.2*P1*0.0980665-6)*(0.345*0.01*Ro/1.2044-0.446*0.001)+0.015)*(1.3-0.0144*(T1-283.2));
		double dP1 = m_dPin;
		double dP2 = m_dPout;
		double nu = 1-(dP1+dP2)/(P2-P1);
		double Q = m_rQout;
		m_A = c1*1/z*1/T1*nu*(P2*P2-P1*P1)*Q;
		m_B = 1e3*m_rsQtg*m_rHin*0.238846/*ккал/м3*//7000.;

		// Политропная работа сжатия КЦ по РД-151
		double E = (P2+m_dPout)/(P1-m_dPin);
		m_rsL = 320.25*z*T1*m_rQout*(pow(E, 0.3)-1);
	}

	void BShop::ImportGroupResults()
	{
		if (!m_pGroup)
			return;
		m_rPin = m_pGroup->m_rPin;		// Давление на входе объекта [ата]
		m_rTin = m_pGroup->m_rTin;		// Температура на входе объекта [0С]
		m_rQin = 0;						// Расход газа на входе объекта [млн.м3/сут]
		m_rPout = m_pGroup->m_rPout;		// Давление на выходе объекта [ата]
		m_rTout = m_pGroup->m_rTout;		// Температура на выходе объекта [0С]
		m_rQout = 0;						// Расход газа на выходе объекта [млн.м3/сут]
		m_rsQtg = 0;								// Расход топливного газа [млн.м3/сут]
		m_rsQon = 0;								// Расход газа на собственные нужды [млн.м3/сут]
	}

	void BShop::ExportResults(ostream &out)
	{
		BObject::ExportResults(out);
		out << " " <<
			m_rCO2 << " " <<
			m_rN2;
	}

	void BShop::ExportDynamicsData()
	{
		assert(m_pMap);

		DMapFile &MapFile = *m_pMap;
		MapFile << float(m_rPin);
		MapFile << float(m_rQin);
		MapFile << float(m_rTin);
		MapFile << float(m_rPout);
		MapFile << float(m_rQout);
		MapFile << float(m_rTout);
	}

	void BShop::ResultsToObject()
	{
		for (unordered_map <int, BShopGPAGroup*>::iterator i = m_WorkingGroups.begin(); i != m_WorkingGroups.end(); i++)
		{
			delete i->second;
		}
		m_WorkingGroups.clear();
		m_pGroupDisabled->m_pGPAs.clear();

		// В цикле по группам данного КЦ в результате расчета
		list <BShopGPA*> rWorkingGPAs;
		m_nWGroupsCount = m_rWorkingGroups.size();
		m_nShopGPAReserve = m_nShopGPAs;
		for (unordered_map <int, BShopGPAGroup*>::iterator i = m_rWorkingGroups.begin(); i != m_rWorkingGroups.end(); i++)
		{
			BShopGPAGroup *wGroup = i->second;
			BShopGPAGroup *pGroup = new BShopGPAGroup;
			pGroup->m_ID = wGroup->m_ID;
			AddGroup(pGroup);
			pGroup->m_nStages = wGroup->m_nStages;
			m_nShopGPAReserve -= pGroup->m_nStages;
		
			// Далее в цикле по ступеням данной группы ГПА
			for (vector <BShopGPA*>::iterator j = wGroup->m_pGPAs.begin(); j != wGroup->m_pGPAs.end(); j++)
			{
				BShopGPA *pShopGPA = *j;
				pGroup->AddShopGPA(pShopGPA);
				pShopGPA->ResultsToObject();
				rWorkingGPAs.push_back(pShopGPA);
			}
		}

		// Далее в цикле по выключенным ГПА
		for (vector <BShopGPA*>::iterator i = m_pAllGPAs.begin(); i != m_pAllGPAs.end(); i++)
		{
			BShopGPA *pShopGPA = *i;
			if (find(rWorkingGPAs.begin(), rWorkingGPAs.end(), pShopGPA) == rWorkingGPAs.end())
			{
				m_pGroupDisabled->AddShopGPA(pShopGPA);
			}
		}

		if (gData.m_TMode != OptEnums::TMode::T_Opt)
		{
			m_nAVOCount = m_rsAVOcount;
			m_nVentAVOCount = m_rsAVOVent;
		}

		m_dE = m_rsE;
		m_dQ = m_rsQtg;
		m_dT = m_rTout-m_rTin;
	}

	void BShop::InputShopResults(istream &in)
	{
		for (unordered_map <int, BShopGPAGroup*>::iterator i = m_rWorkingGroups.begin();	i != m_rWorkingGroups.end(); i++)
			delete i->second;
		m_rWorkingGroups.clear();

		string s;
		int nGroupsCount = 0;
		in >> nGroupsCount;
		in >> m_rPin;
		in >> m_rTin;
		in >> m_rQin;
		in >> m_rsE;
		in >> m_rPout;
		in >> m_rsTng;
		in >> m_rTout;
		in >> m_rQout;
		in >> m_rsQtg;
		in >> m_rsQon;
		in >> m_rsW;
		in >> m_rsN;
		in >> m_rsNres;
		in >> m_rsQb;
		in >> m_rsAVOcount;
		in >> m_rsAVOVent;
		in >> m_rsWAVO;

		getline(in, s);

		//m_rsWAVO = m_rsAVOVent*

		m_rsQtgCost = m_Qcost*m_rsQtg;		// тыс.руб.
		m_rsWCost = m_Wcost*m_rsW/1e3;		// тыс.руб.	
		m_rsWAVOCost = m_Wcost*m_rsWAVO/1e3;	// тыс.руб.	

		for (int i = 0; i<nGroupsCount; i++)
		{
			BShopGPAGroup *pGroup = new BShopGPAGroup;

			int nStages = 0;
			in >> nStages;
			pGroup->m_nStages = nStages;
			getline(in, s);
			for (int j = 0; j<nStages; j++)
			{
				int nGPAGroup = 0;
				int nGPAShop = 0;
				in >> pGroup->m_ID;
				pGroup->m_ID = i+1; // временно
				in >> nGPAGroup;
				in >> nGPAShop;

				if(m_GPAs.find(nGPAShop) == m_GPAs.end())
				{
					getline(in, s);
					continue;
				}
				BShopGPA *pShopGPA = m_GPAs[nGPAShop];
				pShopGPA->InputShopResults(in);
				pGroup->AddShopGPA(pShopGPA);
				getline(in, s);
			}

			AddGroup(pGroup, true);
		}
	}

	void BShop::CheckResults()
	{
		if (m_bPostCalculated)
			return;
		if (m_rQin<0)
		{
			AddAlert(new CAlert(this, "Противоток в КЦ", OptEnums::AlertType::A_Shop_Flowback));
		}
		if (m_rQin>120.0)
		{
			AddAlert(new CAlert(this, "Превышение максимальной производительности пылеуловителей", OptEnums::AlertType::A_Excess_Shop_Qmax));
		}
		if (m_rPout>m_Poutmax)
		{
			AddAlert(new CAlert(this, "Превышение максимального давления на выходе КЦ", OptEnums::AlertType::A_Excess_Shop_Pmax));
		}
	}

	void BShop::InitForExport()
	{
		BObject::InitForExport();
		for_each(m_pAllGPAs.begin(), m_pAllGPAs.end(), bind(&BObject::InitForExport, _1));
		for_each(m_Bypasses.begin(), m_Bypasses.end(), bind(&BObject::InitForExport, _1));
	}

	void BShop::SetCalculated(bool bCalculated)
	{
		BObject::SetCalculated(bCalculated);
		for_each(m_pAllGPAs.begin(), m_pAllGPAs.end(), bind(&BObject::SetCalculated, _1, bCalculated));
		for_each(m_Bypasses.begin(), m_Bypasses.end(), bind(&BObject::SetCalculated, _1, bCalculated));
	}

	void BShop::PostCalculate(bool bPostCalculateChilds)
	{
		if (m_bPostCalculated)
			return;
		//if (bPostCalculateChilds)
		{
			for_each(m_pAllGPAs.begin(), m_pAllGPAs.end(), bind(&BObject::PostCalculate, _1, bPostCalculateChilds));
			for_each(m_Bypasses.begin(), m_Bypasses.end(), bind(&BObject::PostCalculate, _1, bPostCalculateChilds));
		}
		BObject::PostCalculate(bPostCalculateChilds);	
	}

	void BShop::ExportShopResults(ostream &out)
	{
		if (IsFlowMode())
			return;
		if (!m_rWorkingGroups.size())
			return;

		int nGroups = m_rWorkingGroups.size();

		out << m_ID << endl;
		out << 
			nGroups << " " << 
			m_rPin << " " << 
			m_rTin << " " << 
			m_rQin << " " << 
			m_rsE << " " << 
			m_rPout << " " << 
			m_rsTng << " " << 
			m_rTout << " " << 
			m_rQout << " " << 
			m_rsQtg << " " << 
			m_rsQon << " " << 
			m_rsW << " " << 
			m_rsN << " " << 
			m_rsNres << " " << 
			m_rsQb << " " << 
			m_rsAVOcount << " " << 
			m_rsAVOVent;

		for (unordered_map <int, BShopGPAGroup*>::iterator i = m_rWorkingGroups.begin(); i != m_rWorkingGroups.end(); i++)
		{
			BShopGPAGroup *pGroup = i->second;
			int Stages = pGroup->m_pGPAs.size();
			out << endl << Stages;

			int nGPAGroup = 1;
			for (vector <BShopGPA*>::iterator i = pGroup->m_pGPAs.begin(); i != pGroup->m_pGPAs.end(); i++)
			{
				BShopGPA *pShopGPA = *i;
				out << 
					endl <<
					pGroup->m_ID << " " <<
					nGPAGroup  << " " <<
					pShopGPA->m_Number;
				pShopGPA->ExportShopResults(out);
				nGPAGroup++;
			}
		}

		out << endl;
	}

	bool BShop::PrintInitData(ostream &out, bool bOut)
	{
		if(bOut)
		{
			out <<
				m_rPout << " " <<
				m_rTout << " " <<
				m_rRo_out << " " <<
				m_rHout << " " <<
				m_rN2 << " " <<
				m_rCO2 <<
			endl;
		}
		else
		{
			out <<
				m_rPin << " " <<
				m_rTin << " " <<
				m_rRo_in << " " <<
				"0.00" << " " <<
				"0.00" << " " <<
				"0.00" <<
			endl;
		}
		return true;
	}

	// Расчитывает kmin - максимальное значение поправки на обороты всех ГПА, 
	// при котором все ГПА выходят на минимальные обороты 
	// Расчитывает kmax - максимальное значение поправки на обороты всех ГПА, 
	// при котором все ГПА выходят на максимальные обороты 
	void BShop::CalcKnRange(double &kmin, double &kmax)
	{
		kmin = 0; 
		kmax = 0;
		for (unordered_map <int, BShopGPAGroup*>::iterator i = m_rWorkingGroups.begin();	i != m_rWorkingGroups.end(); i++)
		{
			BShopGPAGroup *pGroup = i->second;
			int Stages = pGroup->m_pGPAs.size();

			for (vector <BShopGPA*>::iterator i = pGroup->m_pGPAs.begin(); i != pGroup->m_pGPAs.end(); i++)
			{
				BShopGPA *pShopGPA = *i;
				assert(pShopGPA && pShopGPA->m_pNSIGPA);

				kmin = max(kmin, pShopGPA->m_nmin/pShopGPA->m_n);
				kmax = max(kmax, pShopGPA->m_nmax/pShopGPA->m_n);
			}
		}
	}

	string BShop::GetName()
	{
		return m_Name;
	}

	bool BShop::GetPminMax(double& Pmin, double& Pmax)
	{
		Pmin = m_Pinmin;
		Pmax = m_Poutmax;
		Pmax -= m_dPout;
		return true;
	}

	void BShop::GetManagedParamBorders(RManagedParam *pParam, double &min, double &max)
	{
		min = 10e10;
		max = -10e10;
		if (pParam->m_Code == OParam::O_E)
		{
			min = std::min(min, m_Emin);
			max = std::min(max, m_Emax);
			min = min ? min : 1.1;
			max = max ? max : 2.0;
		}
	}

	void BShop::SummA(double *pA, OptEnums::TypeA type)
	{
		if (!m_bCalculated)
			return;

		if ((m_rPout-m_rPin)<0.001)
			return;
		if (m_rQout<0.001)
			return;

		// Расчет показателей энергоэффективности
		double c1 = 10.138;
		double P1 = m_rPin;
		double P2 = m_rPout;
		double Ro = m_rRo_in;
		double T1 = m_rTin+273.15;
		double T2 = m_rTout+273.15;

		double z = 1-((10.2*P1*0.0980665-6)*(0.345*0.01*Ro/1.2044-0.446*0.001)+0.015)*(1.3-0.0144*(T1-283.2));
		double zout = 1-((10.2*P2*0.0980665-6)*(0.345*0.01*Ro/1.2044-0.446*0.001)+0.015)*(1.3-0.0144*(T2-283.2));

		double dP1 = m_dPin;
		double dP2 = m_dPout;
		double nu = 1-(dP1+dP2)/(P2-P1);
		double Q = m_rQout;
	
		P2 += dP2;
		P1 -= dP1;

		const double c = 10.138;
		switch (type)
		{
		case OptEnums::TypeA::A_ttr:
			{
				break;
			}
		case OptEnums::TypeA::A_ettr:
			{
				(*pA) += c1*1/z*1/T1*nu*(P2*P2-P1*P1)*Q; // формула 9.6 расчета ЭТТР ЛУ, методика энергоаудита ГТС (СТО Газпром 2.120-114-2007)
				// Вычисление работы, отдаваемой на СТН КЦ, формула 9.13, методика энергоаудита ГТС (СТО Газпром 2.120-114-2007)
				double Astn = c1*P1*P1*m_rsQtg/(z*T1);
				(*pA) -= Astn;
				break;
			}
		case OptEnums::TypeA::A_ottr:
			{
				(*pA) += (z+zout)/2*(T1+T2)/2*log(P2/P1)*Q; //c1*1/z*1/T1*nu*log(P2/P1)*Q;
				//(*pA) += (z+zout)/2*(T1+T2)/2*log(P2/P1)*Q*P1/(z*T1); //c1*1/z*1/T1*nu*log(P2/P1)*Q;
				break;
			}
		default:
			{
				assert(FALSE);
			}
		};
	}

}