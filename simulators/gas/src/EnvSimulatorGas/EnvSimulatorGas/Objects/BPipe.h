#pragma once

namespace Objects
{
	class BPipe : public BObject
	{
	public:
		BPipe(void);
		virtual ~BPipe(void);
		virtual void LoadData(istream&);
		virtual bool CheckLoadedData(string& Error);
		virtual int GetMatrixID();
		virtual void PostAdd();
		virtual void PostErased();
		virtual void PrintExportData(ostream&);
		virtual void ImportResults(istream&);
		virtual void ExportResults(ostream&);
		virtual void ClearResults();
		virtual bool PrintInitData(ostream&, bool bOut=true);
		virtual bool GetPminMax(double& Pmin, double& Pmax);
		virtual bool IsPipe() { return true; }
		virtual void SummA(double *pA, OptEnums::TypeA type);

	public:
		int m_Type;				// ��� ����� (0 � ����������, 2 � �����, 3 � ����� ��� ������, 7 - ����� ������� ��)
		int m_Thread;			// ����� ����� ��
		double m_Kef;			// �������������� �������������
		double m_Kto;			// ����. ������������� �� ���� � ���������� ����� [��/(�2 ����)]
		double m_T;				// ����������� ���������� ����� [0�]
		double m_Pmin;			// ���������� ���������� �������� ���� � ����� [���]
		double m_Pmax;			// ����������� ���������� �������� ���� � ����� [���]
		double m_d;				// ���������� ������� ����� [��]
		double m_D;				// �������� ������� ����� [��]
		double m_L;				// ����� ����� [��]
		double m_k;				// ����. �����-�� ����� [��]
		double m_dh;			// �������� ����� [�]

		// ���������� �������
		double m_rVin;			// �������� ������ �� �����
		double m_rVout;			// �������� ������ �� ������
		double m_rQv;			// ����� ���� � ����� (���.�3)
		double m_rDirection;	// ������� ����.������(�����)1-�� ���./0
	};
}