#pragma once

#include "BValve.h"

namespace Objects
{
	class BRDValve : public BValve
	{
	public:
		BRDValve(void);
		virtual ~BRDValve(void);
		virtual void LoadData(istream&);
		virtual bool CheckLoadedData(string& Error);
		virtual int GetMatrixID();
		virtual void PostAdd();
		virtual void PostErased();
		virtual void ClearResults();
		virtual void PrintExportData(ostream&);
		virtual void ImportAdaptation(istream&);		
		virtual void ExportAdaptation(ostream&);
	
	public:
		int m_Type;			// ��� ����� (0 � ��������� ��� �������, 1 � ���������� �������� ��� ��������� ����)
		double m_Pinmin;	// ���������� ���������� �������� ���� ����� ������ [���]
		double m_Poutmax;	// ����������� ���������� �������� ���� �� ������ ����� [���]
		double m_Pset;		// ������� �������� ���� �� ������ ���������� [���]
		double m_DWhole;	// ������� ��������� ��������� ����� [��]
		double m_d;			// �������� ������� ����� [��]
		double m_k;			// ����.������� ������������� �����

		// ���������� �������
		double m_rd;			// �������� ������� ����� [��]
		double m_rk;			// ����.������� ������������� �����
	};
}