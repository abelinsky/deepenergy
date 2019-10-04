#pragma once

#include "BShop.h"

namespace Objects
{
	class RShopsGroupRollbackParams : public RRollbackParams
	{
	public:
		RShopsGroupRollbackParams(void)
		{
			m_dEOld = 0;
			m_dPOld = 0;
			m_dTOld = 0;
			m_dQOld = 0;
		}
		virtual ~RShopsGroupRollbackParams(void){}
		double m_dEOld;
		double m_dPOld;
		double m_dTOld;
		double m_dQOld;
	};

	class RShopsGroup : public BObject
	{
		friend class CConnectionsMatrix;
	public:
		RShopsGroup(void);
		virtual ~RShopsGroup(void);
		virtual int GetMatrixID();
		virtual bool IsShopGroup() { return true; }
		virtual void PostAdd();
		virtual void PostErased();
		void AddShop(BShop*);
		void EraseShop(BShop*);
		virtual void GetManagedParamBorders(RManagedParam*, double &min, double &max);
		virtual void SetParamValue(RManagedParam*, double Value);		
		virtual void Off();
		virtual void On();
		bool IsOff();
		virtual double GetParamDelta(RManagedParam*);
		void SetFlowMode(bool bFlowMode = true);
		virtual bool IsFlowMode() { return (m_bFlowModel || m_bForceFlowMode); }
		virtual void SetCalculated(bool bCalculated = true);
		virtual void RebuildName();
		
		virtual bool CanExport();
		void PrintExportLosts(ostream& lost_ad, ostream& lost);
		virtual void ClearResults();
		virtual void ImportResults(istream&);
		virtual void ResultsToObject();
		virtual void PostCalculate(bool bPostCalculateChilds = false);	
		virtual void CheckResults();
		virtual void Rollback(RRollbackParams *pRollbackStorage = NULL);
		virtual void StoreParams(RRollbackParams *pRollbackStorage = NULL);

		double GetEmin();
		double GetEmax();

	public:
		vector <BShop*> m_pShops;							// Массив КЦ
		bool m_bFlowModel;
		bool m_bForceFlowMode;								// Принудительный признак, что группа рассчитывается в потоковом режиме
		double m_rCO2;										// % СО2
		double m_rN2;										// % N2
		double m_Tftg;										// Температура грунта на КС [0С]

		double m_dPin_max;									// максимальные потери во входных коммуникациях КЦ
		double m_dPout_max;									// максимальные потери в выходных коммуникациях КЦ

		double m_dPin_min;									// минимальные цеховые потери во входных коммуникациях
		double m_dPout_min;									// минимальные цеховые потери в выходных коммуникациях

		double m_rsE;										// Степень сжатия
		double m_rsQtg;										// Расход топливного газа [млн.м3/сут]
		double m_rsW;										// Расход электроэнергии [кВт/час]
		double m_rsEff;										// Удельный показатель эффективности расхода газа на СТН на единицу ЭТТР, [м3/млн.м3*км]
		double m_rsQmin;									// Минимальный расход при двух давлениях m_rsPin, m_rsPout, полученных при решении потоковой модели
		double m_rsQmax;									// Максимальный расход при двух давлениях m_rsPin, m_rsPout, полученных при решении потоковой модели
		double m_rsN;										// Оценка потребляемой мощности, определенная по упрощенной формуле
		double m_rsQbypass;									// Расход байпасирования [млн.м3/сут] (только если есть дырка в схеме)

		double m_dE;										// Степень сжатия, для потокового режима 
		double m_dP;										// Дельта Р, для потокового режима 
		double m_dT;										// Дельта Т, для потокового режима
		//double m_Tout;										// Уставка выходной температуры группы, используемая в расчете
		double m_setTout;									// Заданная пользователем уставка выходной температуры группы
		double m_dQ;										// Дельта Q, для потокового режима 

		double m_Qmax;										// Предустановленный максимальный расход через КС [млн.м3/сут]

		RShopsGroupRollbackParams m_Rollback;

		bool m_bOptimized;									// Признак, имеются ли расчетные схемы КС
		int m_dv1;											// Производная, текущий критерий

		double m_Emax;										// Максимально-допустимая степень сжатия
		double m_Emin;										// Минимально-допустимая степень сжатия
	};

	static int CALLBACK LostGroupsCounter(BObject *pObject)
	{
		RShopsGroup *pGroup = dynamic_cast<RShopsGroup*>(pObject);
		if (!pGroup)
			return 0;
		return pGroup->CanExport()?1:0;
	}

	static bool CALLBACK C_EFF(const RShopsGroup* Group1, const RShopsGroup* Group2)
	{
		return Group1->m_rsEff<Group2->m_rsEff;
	}
	static bool CALLBACK C_DV(const RShopsGroup* Group1, const RShopsGroup* Group2)
	{
		return Group1->m_dv1<Group2->m_dv1;
	}
}