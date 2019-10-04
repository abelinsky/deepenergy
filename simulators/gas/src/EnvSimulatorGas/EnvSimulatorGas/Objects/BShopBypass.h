#pragma once

#include "BShopObject.h"

namespace Objects
{
	class BShopBypass : public BShopObject
	{
	public:
		BShopBypass(void);
		virtual ~BShopBypass(void);
		virtual void LoadData(istream&);
		virtual bool CheckLoadedData(string& Error);
		virtual void PrintExportData(ostream&);
		virtual void PostAdd();
		virtual void PostErased();
	
	public:
		int m_Number;			// �������������� ����� ����� � ��
		int m_Type;				// ��� ����� 0-���������, 1-������
		int m_ConnectionType;	// ��� ��������� ����� � ������� �� 0-���� ����� �� ���, 1-����� ���
		double m_DWhole;		// ������� ��������� ��������� ����� [��]
		double m_d;				// �������� ������� ����� [��] (���� ��� ����� - ������, �� ������ ��������� � ��������� ��������� ��������� �����).
//		int m_oParam;			// ���� ���� �������� ����� ���� (��� ������ �����������), �� �������, ��� �������� ����� ��������������. 
								// ��� ����, ��� ���������� ������������ ������� �������� �����, � ��� ������� - ������ ��� ������
		double m_k;				// ����. ������������� �����
	};
}