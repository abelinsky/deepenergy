#pragma once

namespace Objects
{
	class BIn : public BObject
	{
	public:
		BIn(void);
		virtual ~BIn(void);
		virtual bool CheckLoadedData(string& Error);
		virtual void PostAdd();
		virtual void PostErased();
		virtual void PrintExportData(ostream&);
		virtual void ExportResults(ostream&);
		virtual void ClearResults();
		virtual bool PrintInitData(ostream&, bool bOut=true);
		virtual void ImportResults(istream&);
		virtual bool IsIn() { return true; }
		virtual void SummA(double *pA, OptEnums::TypeA type);

	public:
		int m_Node; // ���� �����
		double m_P;
		double m_Q;
		double m_T;
		double m_Ro;
		double m_N2;
		double m_C02;
		double m_H;

		// ���������� �������
		double m_rP;	//�������� � ���� [���]
		double m_rT;	//����������� [0�]
		double m_rRo;	//������������� ��������� ����
		double m_rH;	//������ ������������ ����������� ���� �� ����� ������� []
		double m_rQ;	//������ ���� [���.�3/���]
		double m_rCO2;	//%��2
		double m_rN2;	//%N2
	};

	class BInOut
	{
	public:
		static bool LoadData(istream&, string& Error);
	};
}