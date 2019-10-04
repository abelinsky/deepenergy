#include "pch.h"
#include "BShop.h"
#include "RShopsGroup.h"
#include "Objects.h"

namespace Objects {

RShopsGroup::RShopsGroup(void)
{
	m_bFlowModel = false;
	m_bForceFlowMode = false;
	m_dE = 1;
	m_dP = 0;
	m_dT = 0;
	m_dQ = 0;
	m_Emin = 1.05;
	m_Emax = 3;
	m_Tftg = 0;
	ClearResults();
	m_pParams[OParam::O_E] = new RManagedParam(this, &m_dE, OParam::O_E);
	m_pParams[OParam::O_T] = new RManagedParam(this, &m_setTout, OParam::O_T);
	// m_setTout = 18;
	m_rTout = m_setTout;
	m_dv1 = 0;
	m_Qmax = 0;
	m_dPin_max = 0;
	m_dPout_max = 0;

	m_dPin_min = 1e3;
	m_dPout_min = 1e3;
}

RShopsGroup::~RShopsGroup(void)
{
}

void RShopsGroup::PostAdd()
{
	CObjectsModel *pModel = GetModel();
	pModel->m_ParallelShops.push_back(this);

	BPipe *pPipe = NULL;
	CNode *pStartNode = pModel->m_Connections.GetNode(m_NodeStart);
	CNode *pEndNode = pModel->m_Connections.GetNode(m_NodeEnd);
	if (pStartNode)
	{
		for (vector <int>::iterator i = pStartNode->m_InEdges.begin(); i != pStartNode->m_InEdges.end(); i++)
		{
			BPipe *pPipeObject = dynamic_cast<BPipe*>(pModel->GetObject(*i));
			if (pPipeObject)
			{
				pPipe = pPipeObject;
				break;
			}
		}

		for (vector <int>::iterator i = pStartNode->m_Ins.begin(); i != pStartNode->m_Ins.end(); i++)
		{
			BIn *pIn = dynamic_cast<BIn*>(pModel->GetObject(*i));
			if (!pIn)
				continue;
			bool bSource = (pIn->m_P > 0);
			if (bSource && pEndNode)
			{
				//m_Emax = min(m_Emax, pEndNode->m_Pmax/pIn->m_P);
			}
		}
	}

	if (!pPipe)
	{		
		if (pEndNode)
		{
			for (vector <int>::iterator i = pEndNode->m_InEdges.begin(); i != pEndNode->m_InEdges.end(); i++)
			{
				BPipe *pPipeObject = dynamic_cast<BPipe*>(pModel->GetObject(*i));
				if (pPipeObject)
				{
					pPipe = pPipeObject;
					break;
				}
			}
		}
	}

	if (pPipe)
		m_Tftg = pPipe->m_T;
}

void RShopsGroup::PostErased()
{
	vector <RShopsGroup*>::iterator i = find(GetModel()->m_ParallelShops.begin(), GetModel()->m_ParallelShops.end(), this);
	if (i != GetModel()->m_ParallelShops.end())
	{
		GetModel()->m_ParallelShops.erase(i);
	}
}

void RShopsGroup::ClearResults()
{
	BObject::ClearResults();
	m_rsE = 0;
	m_rsW  = 0;
	m_rCO2 = 0;
	m_rN2 = 0;
	m_rsQmin = 0;
	m_rsQmax = 0;
	m_rsN = 0;
	m_rsQtg = 0;
	m_rsEff = 0;
	m_rsQbypass = 0;
	m_bOptimized = false;
}

void RShopsGroup::AddShop(BShop *pShop)
{
	if (!m_SID.empty())
	{
		m_SID += "_";
	}
	if (m_pShops.empty())
	{
		m_SID += pShop->GetName();
	}
	else
	{
		m_SID += itos(pShop->m_ShopNumber);
	}

	string_replace(m_SID, " ", "_");

	m_pShops.push_back(pShop);
	
	m_Qmax += pShop->m_Qmax;
}

void RShopsGroup::RebuildName()
{
	m_SID = "";
	bool bFirst = true;
	for (vector <BShop*>::iterator i = m_pShops.begin(); i != m_pShops.end(); i++)
	{
		BShop *pShop = *i;
		if (bFirst)
		{
			m_SID += pShop->GetName();
			bFirst = false;
		}
		else
		{
			m_SID += "_";
			m_SID += itos(pShop->m_ShopNumber);
		}
	}
}

void RShopsGroup::EraseShop(BShop *pShop)
{
	vector <BShop*>::iterator i = find(m_pShops.begin(), m_pShops.end(), pShop);
	if (i != m_pShops.end())
	{
		m_pShops.erase(i);
	}
	m_SID += "xКЦ" + itos(pShop->m_ShopNumber);
}

double RShopsGroup::GetEmin()
{
	double eMin = 1e6;
	double eMax = -1e6;
	GetManagedParamBorders(GetParam(OParam::O_E), eMin, eMax);
	return eMin;
}

double RShopsGroup::GetEmax()
{
	double eMin = 1e6;
	double eMax = -1e6;
	GetManagedParamBorders(GetParam(OParam::O_E), eMin, eMax);
	return eMax;
}

void RShopsGroup::GetManagedParamBorders(RManagedParam *pParam, double &min, double &max)
{
	min = 10e10;
	max = -10e10;
	if (pParam->m_Code == OParam::O_OB)
	{
		for (auto i = m_pShops.begin(); i != m_pShops.end(); i++)
		{
			BShop *pShop = *i;
			double g = 0, l = 0;
			pShop->CalcKnRange(g, l);
			if (g || l)
			{
				min = std::min(min, g);
				max = std::max(max, l);
			}
		}
	}

	if (pParam->m_Code == OParam::O_E)
	{
		min = m_Emin;
		max = m_Emax;


		// По степеням сж.ГПА
		if (m_rPin*m_rPout>0)
		{
			//min = min*(1-m_dPin_max/m_rPin)/(1+m_dPout_max/m_rPout);
			//max = max*(1-m_dPin_max/m_rPin)/(1+m_dPout_max/m_rPout);

			min = min*(1-m_dPin_min/m_rPin)/(1+m_dPout_min/m_rPout);
			max = max*(1-m_dPin_max/m_rPin)/(1+m_dPout_max/m_rPout);
		}
	}

	if (pParam->m_Code == OParam::O_T) // Температура выхода ГКЦ
	{
		min = 0.;
		max = 80.;
	}
}

void RShopsGroup::SetParamValue(RManagedParam *pParam, double Value)
{
	if (pParam->m_Code == OParam::O_E) // Поправки на степ.сж.
	{
		for (vector <BShop*>::iterator i = m_pShops.begin(); i != m_pShops.end(); i++)
		{
			BShop *pShop = *i;
			if (pShop->m_bWShop)
				continue;
			pShop->m_dE = Value;
		}
	}
	BManagedObject::SetParamValue(pParam, Value);
}

void RShopsGroup::SetFlowMode(bool bFlowMode)
{
	if (!bFlowMode && ((m_dE<=1.05) || m_bForceFlowMode))
		return;
	m_bFlowModel = bFlowMode;
	for_each(m_pShops.begin(), m_pShops.end(), bind(&BShop::SetFlowMode, _1, bFlowMode));
	GetModel()->m_bSchemeChanged = true;
}

void RShopsGroup::CheckResults()
{
	if (!m_bOptimized && (m_rQin>=m_rsQmin) && (m_rQin<=m_rsQmax)) // "дырка"
	{
		AddAlert(new CAlert(this, "'Дырка' в режиме КС", OptEnums::AlertType::A_ShopsGroupHole));
	}
}

void RShopsGroup::PostCalculate(bool bPostCalculateChilds)
{
	if (m_bPostCalculated)
		return;

	if (m_bCalculated)
	{
		m_rsQtg = m_rQin-m_rQout;
		m_rsE = m_rPout/m_rPin;
		m_rsN = (72.4*m_rPin*m_rQin/0.8)*(pow(m_rsE, 0.245)-1);

		m_dE = m_rPout/m_rPin;
		m_dP = m_rPout-m_rPin;		

		m_dT = m_rTout-m_rTin;
		m_dQ = m_rsQtg;

		if (bPostCalculateChilds)
			for_each(m_pShops.begin(), m_pShops.end(), bind(&BShop::PostCalculate, _1, bPostCalculateChilds)); // +alerts
	}
	else
	{
		m_rQin = 0;
		m_rQout = 0;
		m_rsQtg = 0;
		m_dQ = 0;
		for (vector <BShop*>::iterator i = m_pShops.begin(); i != m_pShops.end(); i++)
		{
			BShop *pShop = *i;
			if (!pShop->m_bCalculated)
				continue;
			if (!pShop->m_bPostCalculated)
				pShop->PostCalculate(bPostCalculateChilds);
			m_rPin = pShop->m_rPin;
			m_rTin = pShop->m_rTin;
			m_rQin += pShop->m_rQin;
			m_rPout = pShop->m_rPout;
			m_rTout = pShop->m_rTout;
			m_rQout += pShop->m_rQout;
			m_rsQtg += pShop->m_rsQtg;
			m_rsE = pShop->m_rsE;
			m_rRo_in = pShop->m_rRo_in;
			m_rHin = pShop->m_rHin;
			m_rRo_out = pShop->m_rRo_out;
			m_rHout = pShop->m_rHout;

			m_dE = m_rsE;
			m_dP = m_rPout-m_rPin;
			m_dT = m_rTout-m_rTin;
			m_dQ += pShop->m_rsQtg;
		}
	}
	BObject::PostCalculate(bPostCalculateChilds);
}

bool RShopsGroup::CanExport()
{
	return IsFlowMode();
}

int RShopsGroup::GetMatrixID()
{
	return 4;
}

void RShopsGroup::PrintExportLosts(ostream& lost_ad, ostream& lost)
{
	double T = m_dT;
	if ((m_dE > 1.01) && (gData.m_TMode == OptEnums::TMode::T_Set))
		T = m_setTout;
	lost_ad << m_ID << " " << "1" << " " << GetName() << endl;
	lost << m_ID << " " <<
		m_dE << " " <<
		T << " " <<
		m_dQ << " " <<
		"2" << " " <<
		m_Emin << " " <<
		m_Emax << //" " <<
	//	"0" << " " << // Потери давления газа в обвязки КЦ на входе
	//	"0" << " " << // Потери давления газа в обвязки КЦ на выходе
	//	"76" << " " << // Максим. давление газа на выходе КЦ [ата]
	//	"0" << // ID нитки МГ
	endl;
}

void RShopsGroup::ImportResults(istream& in)
{
	BObject::ImportResults(in);
	in >> m_rCO2;
	in >> m_rN2;
	for_each(m_pShops.begin(), m_pShops.end(), bind(&BShop::ImportGroupResults, _1));
}

void RShopsGroup::SetCalculated(bool bCalculated)
{
	BObject::SetCalculated(bCalculated);
	for_each(m_pShops.begin(), m_pShops.end(), bind(&BShop::SetCalculated, _1, bCalculated));
	m_CalculatedEdgesCount = bCalculated?m_pShops.size():0;
}

void RShopsGroup::Off()
{
	RManagedParam *pParam = GetParam(OParam::O_E);
	if (pParam)
	{
		pParam->Off();
	}
	m_Rollback.m_dEOld = m_dE;
	m_Rollback.m_dPOld = m_dP;
	m_Rollback.m_dTOld = m_dT;
	m_Rollback.m_dQOld = m_dQ;

	m_dE = 1;
	m_dP = 0;
	m_dT = 0;
	m_dQ = 0;
}

void RShopsGroup::ResultsToObject()
{
	for_each(m_pShops.begin(), m_pShops.end(), bind(&BShop::ResultsToObject, _1));

	m_dE = m_rPout/m_rPin;
	m_dP = m_rPout-m_rPin;
	m_dT = m_rTout-m_rTin;
	m_dQ = m_rQin-m_rQout;
}

void RShopsGroup::StoreParams(RRollbackParams *pExternalStorage)
{
	RShopsGroupRollbackParams *pStorage = dynamic_cast<RShopsGroupRollbackParams*>(pExternalStorage);
	if (!pStorage)
		pStorage = &m_Rollback;
	pStorage->m_dEOld = m_dE;
	pStorage->m_dPOld = m_dP;
	pStorage->m_dTOld = m_dT;
	pStorage->m_dQOld = m_dQ;
}

void RShopsGroup::Rollback(RRollbackParams *pExternalStorage)
{
	RShopsGroupRollbackParams *pStorage = dynamic_cast<RShopsGroupRollbackParams*>(pExternalStorage);
	if (!pStorage)
		pStorage = &m_Rollback;
	m_dE = pStorage->m_dEOld;
	m_dP = pStorage->m_dPOld;
	m_dT = pStorage->m_dTOld;
	m_dQ = pStorage->m_dQOld;
}

bool RShopsGroup::IsOff()
{
	return (m_dE<1.05);
}

void RShopsGroup::On()
{
	RManagedParam *pParam = GetParam(OParam::O_E);
	if (pParam)
	{
		pParam->On();
	}
	m_dE = m_Rollback.m_dEOld;
	m_dP = m_Rollback.m_dPOld;
	m_dT = m_Rollback.m_dTOld;
	m_dQ = m_Rollback.m_dQOld;
}

double RShopsGroup::GetParamDelta(RManagedParam *pParam)
{
	if (pParam->m_Code == OParam::O_E)
	{
		return 0.003;
	}

	if (pParam->m_Code == OParam::O_T) // Температура выхода ГКЦ
	{
		return 0.1;
	}
	return BManagedObject::GetParamDelta(pParam);
}

}