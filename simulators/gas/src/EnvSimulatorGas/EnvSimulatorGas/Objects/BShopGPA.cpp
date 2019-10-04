#include "pch.h"
#include "BShopGPA.h"
#include "BShop.h"

namespace Objects {

BShopGPA::BShopGPA(void)
{
	m_pParams[OParam::O_OB] = new RManagedParam(this, &m_n, OParam::O_OB);
	m_pNSIGPA = NULL;
	m_Number = 0;
	m_NSIID = 0;
	m_KTSGTU_N = 1.;
	m_KUDmin = 1.;
	m_KNmax = 0.99;
	m_n = 1.;
	m_nmin = 0.5;
	m_nmax = 1.5;
	m_Emin = 1.;
	m_Emax = 3.;
	m_wtime = 0.;
	m_bUtilisation = false;
	m_bRegeneration = false;
	m_bAntiIceSystem = false;
	m_StageAllowed = 0;
	m_KTSQtg = 1.;
	m_KTSCBN_N = 1.;
	m_KTS_K = 1.;
	m_KTS_MK = 1.;
	ClearResults();
}

BShopGPA::~BShopGPA(void)
{
}

int BShopGPA::GetMatrixID()
{
	return 6;
}

void BShopGPA::ClearResults()
{
	BShopObject::ClearResults();
	m_rg_n = 0.;
	m_rgKpol = 0.;
	m_rgPin = 0.;
	m_rgTin = 0.;
	m_rgE = 0.;
	m_rgPout = 0.;
	m_rgTout = 0.;
	m_rgQcomm = 0.;
	m_rgQtg = 0.;
	m_rgQ = 0.;
	m_rgKpom = 0.;
	m_rgW = 0.;
	m_rgN = 0.;
	m_rgNres = 0.;
	m_rgKz = 0.;
}

void BShopGPA::PostAdd()
{
	assert(m_pShop);
	m_pShop->m_pAllGPAs.push_back(this);
	m_pNSIGPA = GetModel()->GetNSIGPA(m_NSIID);
	if (m_pNSIGPA)
	{
		m_pShop->m_bWShop &= (m_pNSIGPA->m_DriveType == 0);
	}
}

void BShopGPA::PostErased()
{
	vector <BShopGPA*>::iterator i = find(m_pShop->m_pAllGPAs.begin(), m_pShop->m_pAllGPAs.end(), this);
	if (i != m_pShop->m_pAllGPAs.end())
	{
		m_pShop->m_pAllGPAs.erase(i);
	}
}

void BShopGPA::LoadData(istream &in)
{
	in >> m_Number;
	in >> m_NSIID;
	in >> m_KTSGTU_N;
	in >> m_KUDmin;
	in >> m_KNmax;
	in >> m_n;
	in >> m_nmin;
	in >> m_nmax;
	in >> m_Emin;
	in >> m_Emax;
	in >> m_wtime;
	in >> m_bUtilisation;
	in >> m_bRegeneration;
	in >> m_bAntiIceSystem;
	in >> m_StageAllowed;
	in >> m_KTSQtg;
	in >> m_KTSCBN_N;
	in >> m_KTS_K;
	if (!eol(in))
		in >> m_KTS_MK;

	GetModel()->m_GPAs.push_back(this);
}

bool BShopGPA::CheckLoadedData(string &Error)
{
	bool bSuccess = true;
	if (!m_pNSIGPA)
	{
		string s;
		// s = string_format("В исходных данных не найден паспорт ГПА с номером %d.\n", m_NSIID);
		s = (boost::format("In the source data not found passport NSIGPA number %d") % m_NSIID).str();
		Error += s;
		bSuccess = false;
	}
	return bSuccess;
}

void BShopGPA::PrintExportData(ostream &out)
{
	double n = m_n;
	double KNmax = m_KNmax;
	double nmin = m_nmin;
	double nmax = m_nmax;
	double KTS_K = m_KTS_K*gData.m_kKTSForce;

	if (!gData.m_bControlRestrictions)
	{
		nmin = 0.3;
		nmax = 1.2;
	}

	//nmin = 0.3;  // временно
	//nmax = 1.2; // временно

	double KTSQtg = m_KTSQtg/gData.m_kKTSGTUQtg;

	out <<
		m_Number << " " <<
		m_NSIID << " " <<
		m_KTSGTU_N << " " <<
		m_KUDmin << " " <<
		KNmax << " " <<
		n << " " <<
		nmin << " " <<
		nmax << " " <<
		m_Emin << " " <<
		m_Emax << " " <<
		m_wtime << " " <<
		m_bUtilisation << " " <<
		m_bRegeneration << " " <<
		m_bAntiIceSystem << " " <<
		m_StageAllowed << " " <<
		KTSQtg << " " <<
		m_KTSCBN_N << " " <<
 		KTS_K << " " <<
		m_KTS_MK <<
	endl;
}

void BShopGPA::ResultsToObject()
{
	m_n = m_rg_n;
}

void BShopGPA::CheckResults()
{
	if (m_bPostCalculated)
		return;
	if ((m_rgKz-m_KNmax)>0.005)
		AddAlert(new CAlert(this, "Превышение максимальной загрузки ГПА по мощности", OptEnums::AlertType::A_Excess_ShopGPA_Kz));
	if ((m_rgKpom>0) && (m_rgKpom<m_KUDmin))
		AddAlert(new CAlert(this, "Попадание ГПА в зону помпажа", OptEnums::AlertType::A_Excess_ShopGPA_Kud));
	if (m_pNSIGPA && (m_rgQ>m_pNSIGPA->m_Qmax))
		AddAlert(new CAlert(this, "Превышение максимально-допустимой объемной производительности ГПА", OptEnums::AlertType::A_Excess_ShopGPA_Qmax));
	if ((m_rg_n>0) && (m_rg_n<m_nmin))
		AddAlert(new CAlert(this, "Расчетные обороты ГПА ниже минимально допустимых", OptEnums::AlertType::A_Excess_ShopGPA_Min_n));
	if ((m_rg_n>0) && (m_rg_n>m_nmax))
		AddAlert(new CAlert(this, "Расчетные обороты ГПА выше минимально допустимых", OptEnums::AlertType::A_Excess_ShopGPA_Max_n));	
}

void BShopGPA::InputShopResults(istream &in)
{
	in >> m_rg_n;
	in >> m_rgKpol;
	in >> m_rgPin;
	in >> m_rgTin;
	in >> m_rgE;
	in >> m_rgPout;
	in >> m_rgTout;
	in >> m_rgQcomm;
	in >> m_rgQtg;
	in >> m_rgQ;
	in >> m_rgKpom;
	in >> m_rgW;
	in >> m_rgN;
	in >> m_rgNres;
	in >> m_rgKz;
}

void BShopGPA::ExportShopResults(ostream &out)
{
	out << 
		" " <<
		m_n << " " <<
		m_rgKpol << " " <<
		m_rgPin << " " <<
		m_rgTin << " " <<
		m_rgE << " " <<
		m_rgPout << " " <<
		m_rgTout << " " <<
		m_rgQcomm << " " <<
		m_rgQtg << " " <<
		m_rgQ << " " <<
		m_rgKpom << " " <<
		m_rgW << " " <<
		m_rgN << " " <<
		m_rgNres << " " <<
		m_rgKz;
}

double BShopGPA::GetParamDelta(RManagedParam *pParam)
{
	if (pParam->m_Code == OParam::O_OB)
	{
		return 0.005;
	}

	return BManagedObject::GetParamDelta(pParam);
}

void BShopGPA::GetManagedParamBorders(RManagedParam *pParam, double &min, double &max)
{
	min = 10e10;
	max = -10e10;
	if (pParam->m_Code == OParam::O_OB)
	{
		//min = 0.3;
		//max = 1.2;

		min = m_nmin;
		max = m_nmax;
	}
}
}