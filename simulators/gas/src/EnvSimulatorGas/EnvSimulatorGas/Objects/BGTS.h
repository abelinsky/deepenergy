#pragma once
#include "BObject.h"

namespace Objects
{
	class BGTS : public BObject
	{
	public:
		BGTS(void);
		virtual ~BGTS(void);
		virtual void LoadData(istream&);
		virtual void PostAdd();
		virtual void PostErased();
		virtual void PrintExportData(ostream&);
	
	public:
		double m_kNmax;					// N����/N��� <=
		bool m_bControlKcharge;			// �������� ����� (���)
		double m_TairAdd;				// �������� �� T���
		double m_TAVO;					// �������� �� �� ������������ ������������� ���������� (������ ���)
		int m_AVOCalc;					// ������� ������� ���
										// -1 � ������ ������ ��� ��� ����� �� ������ �� ����������� �� dT ���
										// 2 � ����������� ������� �������� �����������  (��� ���� ������ ��������� ������� ��� ������ ���-�� ��� � ������������, �������������� ����)
										// ���� � LimitationsGTS.dat ������ �������� ������ 3, � � CompressorShop.dat �� ����� dT ��� ������, ��������, 40, �� ���� ����� �� ������ �� ����������� ����=40
										// ����  � ����� LimitationsGTS.dat �������� "������� ������� ���" �������� ������ 2, �� ��� ��� �� (CompressorShop.dat), ��� � ��� ��������� ������ (Lost.dat) �������� ������� �������� �����������, ���� "������� ������� ���" ����� 1, �� �������� dT.
		double m_Pdrift;				// ����������� �� P
		double m_Qvalidity;				// �������� �� Q���
		double m_Qdrift;				// ����������� �� Q
		bool m_bControlKud;				// �������� ��� (���)
		int m_OptimizationCriteria;		// �������� ����������� ��
										// 0 - �������������
										// 1 - ��������� ���
										// 2 - ��������������
										// 3 - ����������� �������
		int m_PipesCollapse;			// ������������������ (���, ��, �������� ������������������)
		bool m_bIntershopsIgnore;		// ������������ ����� ������� ��
		int m_GroupGRS;					// ������� ����������� ������ ���
		int m_nPointsMax;				// ���������� ����� ���������
		int m_FormulasType;				// ������� ����
		bool m_bKvaziDisable;			// ��������� ��������������
	};
}