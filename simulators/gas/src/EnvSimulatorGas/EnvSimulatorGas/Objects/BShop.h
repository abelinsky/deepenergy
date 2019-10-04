#pragma once
#include "BManagedObject.h"

namespace Objects
{
	class BShopGPA;
	class BShopGPAGroup;
	class BShopBypass;
	class BShopObject;
	class RShopsGroup;
	// ��
	class BShop : public BObject
	{
	public:
		BShop(void);
		virtual ~BShop(void);
		virtual int GetMatrixID();
		virtual void LoadData(istream&);
		virtual bool CheckLoadedData(string& Error);
		void ClearShop();
		bool AddGroup(BShopGPAGroup*, bool bResults = false);
		BShopGPAGroup* GetGroup(int GroupID, bool bResults = false);
		void AddChild(BShopObject*);
		virtual void PostAdd();
		virtual void PostErased();
		virtual bool CanExport();
		void PrintExportLosts(ostream& lost_ad, ostream& lost);
		virtual void PrintExportData(ostream&);
		virtual void ClearResults();
		virtual void ImportResults(istream&);
		virtual void ExportResults(ostream&);
		void InputShopResults(istream&);
		virtual void PostCalculate(bool bPostCalculateChilds = false);
		void ExportShopResults(ostream&);
		virtual bool PrintInitData(ostream&, bool bOut=true);
		virtual string GetName();
		virtual bool GetPminMax(double& Pmin, double& Pmax);
		virtual bool IsFlowMode();
		void SetFlowMode(bool bFlowMode = true);
		virtual bool IsShop() { return true; }
		virtual void GetManagedParamBorders(RManagedParam*, double &min, double &max);
		// ���������� �������� �������� �� ������� ��� �� � ������ �������� ���. � ����. �������� ���
		// � �������� �������� �� �������, �������������� � ������� ��������
		void CalcKnRange(double &kmin, double &kmax);
		virtual void ResultsToObject(); // ������� ����������� �������� � ��������� �� � �������� ��
		virtual void CheckResults();
		void ImportGroupResults();
		virtual void InitForExport();
		virtual void SetCalculated(bool bCalculated = true);
		virtual void SummA(double *pA, OptEnums::TypeA type);
		
	public:
		static unordered_map <int, int> sLoadingMap; // ���������� ���������� "����� ��� � �� - ���������� ���������"

		vector <BShopGPA*> m_pAllGPAs;
		unordered_map <int, BShopGPA*> m_GPAs;
		vector <BShopBypass*> m_Bypasses;
		unordered_map <int, BShopGPAGroup*> m_WorkingGroups;
		BShopGPAGroup* m_pGroupDisabled;
		RShopsGroup* m_pGroup; // ������ ������������ ��, ������� ������

		string m_Name;
		bool m_bWShop;			// ���, ��������� ������ �� ���������������� ���
		string m_KSName;		// �������� ��(char)
		int m_ThreadNumber;		// ����� ����� ��
		int m_ShopNumber;		// ����� ���� 
		double m_kE;			// ����. ��������� �� �� ������� ������
		double m_kK;			// ����. ��������� �� �� ���
		double m_kn;			// ����. ��������� �� �� ��������
		double m_Qcost;			// ���� ���/���. �3    (��������� ���)
		double m_Wcost;			// ���� ���/(��� ���)  (��������������)
		int m_RDValvesCount;	// ���������� ������ ��������������, ����� �������� ���������, ��� ����� �������������� ��������
		double m_dE;			// ������� ������ ��, ��� ���������� ������ 
		double m_dP;			// ������ �, ��� ���������� ������ 
		double m_dT;			// ������ �, ��� ���������� ������ 
		double m_dQ;			// ������ Q, ��� ���������� ������ 
		int m_LostKind;			// ������� ������� ���������� ������ ��: 1 - �� dP, 2 - �� ������� ������
		bool m_bFlowMode;		// �������, ������������� �� �� ��� ��������� ������
		
		double m_Tair;			// ����������� ������� [0�]
		double m_Pair;			// �������� ������� [���]
		double m_Pinmin;		// ���������� ���������� �������� ���� [���]
		double m_Poutmax;		// ����������� ���������� �������� ���� [���]
		double m_Toutmax;		// ����������� ���������� ����������� ���� �� ������ �� [0C]
		double m_dPin;			// ������ �������� �� ����� �� [ ���]
		double m_dPout;			// ������ �������� �� ������ ��  [���] 
		int m_nShopGPAs;		// ����� ���������� ��� � �� 
		int m_nWGroupsCount;	// ���������� ���������� �����
		int m_nShopGPAReserve;	// ���-�� ��� � ������� 
		int m_AVOID;			// ������������� (����) ���� ��� 
		int m_nAVOCount;		// ���������� ���  
		int m_nVentAVOCount;	// ���-�� ���������� ������������
		double m_AVOT_dt;		// ������� ����������� ���� �� ������ ��� [0C]  (dT ����� ����� � ��� �� ��� �����������)
		double m_Poutmin;		// ���������� ���������� �������� ���� �� ������ ��   �������� 0.0
		double m_Qmax;			// ������������ ������ ����������� [���.�3/���] �������� 0.0
		double m_Qtg;			// ������ ���� �� ����������. ����� �� �� [���.�3/���]
		double m_Pset;			// ������� �� �������� ���������� [���] ****
		double m_Emax;			// �����������-���������� ������� ������ ****
		double m_Emin;			// ����������-���������� ������� ������ ****
		int m_CalcType;			// ������ ������ ������� (0 � ����������� ������� � �����,
								// 1 -  ����������� ����� �����. �������,
								// 2 � ������������ � ����� � �������,
								// 3 � ������ �� ���������� ������)
								// 4 � ����������� ���� � �������� ��� ���������� ��

		// ���������� �������

		double m_rCO2;										// % ��2
		double m_rN2;										// % N2

		unordered_map <int, BShopGPAGroup*> m_rWorkingGroups;	// ������
		double m_A;											// ������������� ������������������ ������
		double m_B;											// ������ ��������-�������������� ��������
		double m_rsE;										// ������� ������
		double m_rsTng;										// ����������� ���������� [0�]
		double m_rsQtg;										// ������ ���������� ���� [���.�3/���]		
		double m_rsQon;										// ������ ���� �� ����������� ����� [���.�3/���]
		double m_rsW;										// ������ �������������� [���/���]
		double m_rsN;										// ��������, ������. ��������.  [���]
		double m_rsNres;									// ������ ��������  [���]
		double m_rsQb;										// ������ ��������. [���.�3/���]
		int m_rsAVOcount;									// ���-�� ���.���
		int m_rsAVOVent;									// ���-�� ���� � 1 ���
		double m_rsEff;										// �������� ���������� ������������� ������� ���� �� ��� �� �� ������� ������, [�3/���.�3*��]
		double m_rsL;										// ����������� ������ ������ �� [���*�]
		double m_rsWAVO;									// ������� �/� � ��� [���*�]

		double m_rsQtgCost;									// ��������� ���������� ���� [���.���.]
		double m_rsWCost;									// ��������� ��������������, ����������� ���� [���.���.]
		double m_rsWAVOCost;								// ��������� ��������������, ����������� ��� [���.���.]
	};
}



