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
		vector <BShop*> m_pShops;							// ������ ��
		bool m_bFlowModel;
		bool m_bForceFlowMode;								// �������������� �������, ��� ������ �������������� � ��������� ������
		double m_rCO2;										// % ��2
		double m_rN2;										// % N2
		double m_Tftg;										// ����������� ������ �� �� [0�]

		double m_dPin_max;									// ������������ ������ �� ������� ������������� ��
		double m_dPout_max;									// ������������ ������ � �������� ������������� ��

		double m_dPin_min;									// ����������� ������� ������ �� ������� �������������
		double m_dPout_min;									// ����������� ������� ������ � �������� �������������

		double m_rsE;										// ������� ������
		double m_rsQtg;										// ������ ���������� ���� [���.�3/���]
		double m_rsW;										// ������ �������������� [���/���]
		double m_rsEff;										// �������� ���������� ������������� ������� ���� �� ��� �� ������� ����, [�3/���.�3*��]
		double m_rsQmin;									// ����������� ������ ��� ���� ��������� m_rsPin, m_rsPout, ���������� ��� ������� ��������� ������
		double m_rsQmax;									// ������������ ������ ��� ���� ��������� m_rsPin, m_rsPout, ���������� ��� ������� ��������� ������
		double m_rsN;										// ������ ������������ ��������, ������������ �� ���������� �������
		double m_rsQbypass;									// ������ �������������� [���.�3/���] (������ ���� ���� ����� � �����)

		double m_dE;										// ������� ������, ��� ���������� ������ 
		double m_dP;										// ������ �, ��� ���������� ������ 
		double m_dT;										// ������ �, ��� ���������� ������
		//double m_Tout;										// ������� �������� ����������� ������, ������������ � �������
		double m_setTout;									// �������� ������������� ������� �������� ����������� ������
		double m_dQ;										// ������ Q, ��� ���������� ������ 

		double m_Qmax;										// ����������������� ������������ ������ ����� �� [���.�3/���]

		RShopsGroupRollbackParams m_Rollback;

		bool m_bOptimized;									// �������, ������� �� ��������� ����� ��
		int m_dv1;											// �����������, ������� ��������

		double m_Emax;										// �����������-���������� ������� ������
		double m_Emin;										// ����������-���������� ������� ������
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