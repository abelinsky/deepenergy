#pragma once

#include "BNSI.h"

namespace NSI
{
	class BNSIAVO : public BNSI
	{
	public:
		BNSIAVO(void);
		virtual ~BNSIAVO(void);
		virtual void LoadData(istream&);
		virtual bool CheckLoadedData(string& Error);
		virtual void PrintExportData(ostream&);

	public:
		// m_ID - ���� ���
		string m_Name;			// �������� ���
		int m_PipesCount;		// ���������� ���� � ��� (�������)
		int m_StepsCount;		// ���������� ����� ���� �� ������ � ���  (������ � ��������� ��������� ����������� ���)
		int m_VentCount;		// ���������� ������������ � ��� (�������)
		double m_kFinning;		// ����������� ��������� (������ � ��������� ��������� ����������� ���)
		double m_PipesLength;	// ����� ���� (������ � ��������� ��������� ����������� ���) [�]
		double m_Sout;			// ����������� ����������� �������� (�� ���������) (�������) ��� [�2]
		double m_Sin;			// ����������� ����������� ���������� ��� (�������)  [�2]
		double m_Scutset;		// ������� ����������� ������� ����������� �������  (�������) [�2]
		double m_kTaper;		// ����������� �������
		double m_C;				// ������������� ���������������� ��������� ������ ����� � ���������� ����������� [��/(� . K)]
		double m_QVent;			// ������������������ ����������� [��� �3/�] 
		double m_l;				// ��� ����� ������� [��]
		double m_h;				// ������ �����  [��]
		double m_w;				// ������� ������� ����� [��]
		double m_k;				// ����������� �����������, ����������� ��� ���������, ������������� ����� � �.�.
		double m_N;				// �������� ���������������� �� ���� [���]
	};
}