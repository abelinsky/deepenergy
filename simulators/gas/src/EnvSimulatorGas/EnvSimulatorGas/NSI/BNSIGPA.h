#pragma once

#include "BNSI.h"

namespace NSI
{
	struct KTInterval
	{
		KTInterval()
		{
			m_Tmin = 0.;
			m_Tmax = 0.;
			m_kt = 0.;
			m_T = 0.;
		}
		void operator =(const KTInterval &Source)
		{
			m_Tmin = Source.m_Tmin;
			m_Tmax = Source.m_Tmax;
			m_kt = Source.m_kt;
			m_T = Source.m_T;
		}

		double m_Tmin;		// ����� �������� �����������
		double m_Tmax;		// ������ �������� �����������
		double m_kt;		// ����������� kt
		double m_T;			// ������� ����������� �����������
	};

	class BNSIGPA : public BNSI
	{
	public:
		BNSIGPA(void);
		virtual ~BNSIGPA(void);
		virtual void LoadData(istream&);
		virtual bool CheckLoadedData(string& Error);
		virtual void PrintExportData(ostream&);

		// ���������� ��������� ���
		virtual void CopyForceParams(BNSIGPA *pSource);
		// ���������� ��������� �������
		virtual void CopyDriveParams(BNSIGPA *pSource);

	public:
		// m_ID - ���� ���
		int m_nCharacteristic;		// 1 � ���� (�������� � ���), 2 � ���� (��. ������ � ���)
		int m_DriveType;			// ������� ������� (0-��.������/ 1-���/ 2-���)
		bool m_bWholeHead;			// ������� (1-�������������/ 0-���)
		double m_kNmax;				// �����������-���������� ��������� ����. �������� � �����������
		vector <double> m_kN;		// ������������ ������������� ���������� ��������������
		vector <double> m_kK;		// ������������ ������������� �������������� ���������������� ���
		vector <double> m_kE;		// ������������ ������������� �������� ��������������
		double m_N;					// ����������� �������� [���]
		double m_Qtg;				// ����������� ������ ���������� ���� � ������ ���. ���. [���.�3/���]
		double m_H;					// ����������� ������ ������� �������� [���/�3]
		double m_Tair;				// ����������� ����������� ������� �� ����� ��� [0�]
		double m_Pair;				// ����������� �������� �������� ������� [���]
		double m_Qmin;				// ����������-���������� ����������� ������ [�3/���]
		double m_Qmax;				// �����������-���������� ����������� ������ [�3/���]
		double m_nmin;				// ����������-���������� ������������� �������
		double m_nmax;				// �����������-���������� ������������� �������
		double m_dP;				// ������ �������� ����� ��������� ������  [���]
		double m_Z;					// �����������  ����������� ����������
		double m_T;					// ����������� ���������� [0�]
		double m_R;					// ������� ���������� ���������� [��/�� ����]
		double m_wKPD;				// ��� ����������������
		double m_mKPD;				// ��� ���������������
		double m_kUtil;				// �����������  ������� ������� ����������
		double m_mechKPD;			// ������������ ���
		vector <KTInterval> m_ktIntervals; // ��������� ������������ kt
	};
}