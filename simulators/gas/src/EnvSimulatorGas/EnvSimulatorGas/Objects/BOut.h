#pragma once

namespace Objects
{
	class BOut : public BObject
	{
	public:
		BOut(void);
		virtual ~BOut(void);
		virtual bool CheckLoadedData(string& Error);
		virtual void PostAdd();
		virtual void PostErased();
		virtual void PrintExportData(ostream&);
		virtual void ExportResults(ostream&);
		virtual void ClearResults();
		virtual bool PrintInitData(ostream&, bool bOut=true);
		virtual void ImportResults(istream&);
		virtual bool IsOut() { return true; }
		virtual void ResultsToObject(); // ������� ����������� �������� � ��������� �����������
		virtual void SummA(double *pA, OptEnums::TypeA type);

		void ExportDynamicsData() override;

	public:
		int m_Node; // ���� �����
		int m_nThread; // ������������� �����
		double m_P;
		double m_Q;
		int m_Type;		// Type: 0-������� �����/������, 
						// 1- ��������� ����� ������ ��� ������� �������� �������� ���� � ����,  
						// 2 � ����� ��������, �� � ������. ������ ����� ���� �������,
						// 3 � ��������� ����� ������ ��� ����� �� � ������� P � �)

		// ���������� �������
		double m_rP;	//�������� � ���� [���]
		double m_rT;	//����������� [0�]
		double m_rRo;	//������������� ��������� ����
		double m_rH;	//������ ������������ ����������� ���� �� ����� ������� []
		double m_rQ;	//������ ���� [���.�3/���]
		double m_rCO2;	//%��2
		double m_rN2;	//%N2
		double m_Pmin;  // ����������� �������� �� ����� ���
	};
}




