#pragma once

#include "pch.h"
#include "BManagedObject.h"
#include "DMapFile.h"

namespace Utils
{
	class DMapFile;
}

namespace Objects
{
	class RRollbackParams
	{
	public:
		RRollbackParams(void){}
		virtual ~RRollbackParams(void){}
	};
	class BObject : public BManagedObject
	{
		typedef double (CALLBACK* OBJDPARAM)(BObject *pObject);
		typedef int (CALLBACK* OBJIPARAM)(BObject *pObject);
	public:
		BObject(void);
		virtual ~BObject(void);
		virtual void LoadData(istream&){}
		virtual bool CheckLoadedData(string& Error);
		virtual void PostAdd() = 0;
		virtual void PostErased() = 0;
		virtual void InitForExport();
		virtual bool CanExport();
		virtual void PrintExportData(ostream&){}

		/** Exports dynamics data to shared memory file
			It is assumed that Memory Map file already has approproate position (offset has been already set).
		*/
		virtual void ExportDynamicsData() {}

		/* ��� ����� - (0 � �������� ���� ,1 � �����, 2 � ��, 3 � ���� ��������� ��� ������, 
						4 � ������ ��������� ������ ��������). ��� ������� ���, ��������� �� 
						������ ������� (�����) ����� ������������ ����� ��������� �������:
						5 � ���, 6 � ���, ������� � ������ ������� �������� ��������� ��. 
		*/
		virtual int GetMatrixID();
		virtual void ClearResults();
		virtual void ImportResults(istream&);
		virtual void PostCalculate(bool bPostCalculateChilds = false);// ����� ���������� ����������� ��������
		virtual void SetCalculated(bool bCalculated = true);
		virtual void ExportResults(ostream&);
		virtual void ImportAdaptation(istream&){}
		virtual void ExportAdaptation(ostream&){}
		virtual bool PrintInitData(ostream&, bool bOut=true){return false;}		
		virtual void ResultsToObject(){}
		virtual void CheckResults(){}
		
		virtual double GetPOutMax();

		// ����� ����������
		virtual void F_Count(double* pCounter, OBJDPARAM);
		virtual void I_Count(int* pCounter, OBJIPARAM);

		virtual bool IsFlowMode() { return false; }
		virtual bool IsIn() { return false; }
		virtual bool IsOut() { return false; }
		virtual bool IsShop() { return false; }
		virtual bool IsPipe() { return false; }
		virtual bool IsShopGroup() { return false; }
		static bool OBJCMP(BObject *pObject1, BObject *pObject2);

		// ���������� ����������- � ����������� ���������� ��������, bOut - �� ������, !bOut - �� ����� �������
		virtual bool GetPminMax(double& Pmin, double& Pmax);
		void SetProcessed(bool bProcessed) {m_bProcessed = bProcessed;}
		virtual void Rollback(RRollbackParams *pRollbackStorage = NULL){}
		virtual void StoreParams(RRollbackParams *pRollbackStorage = NULL){}

		// ��������� � ����� �������� ����������� ������
		virtual void SummA(double *pA, OptEnums::TypeA type){}

	public:
		bool m_bProcessed;
		bool m_bCalculated; // �������, ��� ��� ������� ���� ��������� ��������
		bool m_bPostCalculated; // �������, ��� ��� ������ �������� ��������� ��������
		int m_ID;
		int m_NodeStart; // ���� ������
		int m_NodeEnd;	 // ���� �����
		int m_CalculatedEdgesCount; // ���������� ������������ ����� (��� RShopGroup)

		// ���������� �������
		double m_rPin; // �������� �� ����� ������� [���]
		double m_rTin; // ����������� �� ����� ������� [0�]
		double m_rRo_in; // ������������� ��������� ���� �� ����� �������
		double m_rHin;  // ������ ������������ ����������� ���� �� ����� �������
		double m_rQin;  // ������ ���� �� ����� ������� [���.�3/���]
		double m_rPout; // �������� �� ������ ������� [���]
		double m_rTout; // ����������� �� ������ ������� [0�]
		double m_rRo_out; // ������������� ��������� ���� �� ������ �������
		double m_rHout; // ������ �������. �������. ���� �� ������ ������� [���/�3]
		double m_rQout;	// ������ ���� �� ������ ������� [���.�3/���]

		DMapFile* m_pMap;
	};	
}
