#pragma once

#include "BShopObject.h"

namespace NSI
{
	class BNSI;
	class BNSIGPA;
}

namespace Objects
{
	class BShopGPA : public BShopObject
	{
	public:
		BShopGPA(void);
		virtual ~BShopGPA(void);
		virtual int GetMatrixID();
		virtual void LoadData(istream&);
		virtual bool CheckLoadedData(string& Error);
		virtual void PrintExportData(ostream&);
		virtual void PostAdd();
		virtual void PostErased();
		virtual void ClearResults();
		void InputShopResults(istream&);
		void ExportShopResults(ostream&);
		void ResultsToObject(); // ������� ����������� �������� � ��������� ���
		virtual void CheckResults();
		virtual double GetParamDelta(RManagedParam*);
		virtual void GetManagedParamBorders(RManagedParam*, double &min, double &max);

	public:
		BNSIGPA* m_pNSIGPA;

	public:
		int m_Number;			// �������������� ����� ��� � ��
		int m_NSIID;			// ������������� ���� ��� (���� ���)
		double m_KTSGTU_N;		// ����. ������������ ��������� ��� (���) �� ��������
		double m_KUDmin;		// ����., ������������ ����������-���������� ����������� �� ���� �������
		double m_KNmax;			// ����., ������������ �����������-���������� �������� ��� �� ��������
		double m_n;				// ������������� ������� ���
		double m_nmin;			// ����������-���������� ������������� ������� *****
		double m_nmax;			// �����������-���������� ������������� ������� *****
		double m_Emin;			// ����������-���������� ������� ������ *****
		double m_Emax;			// �����������-���������� ������� ������ *****
		double m_wtime;			// ����� ��������� ��� [���.���]
		bool m_bUtilisation;	// ������� ������� ������� ���������� �����
		bool m_bRegeneration;	// ������� ������� ������� ����������� 
		bool m_bAntiIceSystem;	// ������� ������� ���������������������� �������
		int m_StageAllowed;		// ������. ������� �������. (0 � �����, 1- � ������, 2 � �� ������, 3- ��� �������� � 1-� ������� ��� ������� ������� ������ �������) *
		double m_KTSQtg;		// ����. ������������ ��������� ��� �� ���������� ����
		double m_KTSCBN_N;		// ����. ������������ ��������� ��� �� ��������
		double m_KTS_K;			// ����. ������������ ��������� ��� �� ���
		double m_KTS_MK;		// ����. ������������ ��������� �� ���.���
		int m_State;			// ���������, 0 - ��������, 1 - ��������

		// ���������� �������
		double m_rg_n;			// ������������� �������
		double m_rgKpol;		// ��������������� ���
		double m_rgPin;			// �������� �� ����� [���]
		double m_rgTin;			// ����������� �� ����� [0�]
		double m_rgE;			// ������� ������
		double m_rgPout;		// �������� �� ������ [���]
		double m_rgTout;		// ����������� �� ������ [0�]
		double m_rgQcomm;		// ������������ ������ ���� [���.�3/���]
		double m_rgQtg;			// ������ ���������� ���� [���.�3/���]
		double m_rgQ;			// �������� ����������� ������ ���� [�3/���]
		double m_rgKpom;		// ����. ����������� �� ���� ������� 
		double m_rgW;			// ������ ��������������  [���/���]
		double m_rgN;			// ��������, ������-��� ����. [���]
		double m_rgNres;		// ������ ��������  [���]
		double m_rgKz;			// ����. �������� ���
	};
}
