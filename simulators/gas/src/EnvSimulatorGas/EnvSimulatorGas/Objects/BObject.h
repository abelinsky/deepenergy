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

		/* Тип ребра - (0 – открытый кран ,1 – труба, 2 – КЦ, 3 – кран регулятор или байпас, 
						4 – объект локальных потерь давления). Для расчета ГТС, состоящей из 
						одного объекта (ребра) можно использовать также следующие объекты:
						5 – АВО, 6 – ГПА, которые в других случаях являются объектами КЦ. 
		*/
		virtual int GetMatrixID();
		virtual void ClearResults();
		virtual void ImportResults(istream&);
		virtual void PostCalculate(bool bPostCalculateChilds = false);// после считывания результатов расчетов
		virtual void SetCalculated(bool bCalculated = true);
		virtual void ExportResults(ostream&);
		virtual void ImportAdaptation(istream&){}
		virtual void ExportAdaptation(ostream&){}
		virtual bool PrintInitData(ostream&, bool bOut=true){return false;}		
		virtual void ResultsToObject(){}
		virtual void CheckResults(){}
		
		virtual double GetPOutMax();

		// сумма параметров
		virtual void F_Count(double* pCounter, OBJDPARAM);
		virtual void I_Count(int* pCounter, OBJIPARAM);

		virtual bool IsFlowMode() { return false; }
		virtual bool IsIn() { return false; }
		virtual bool IsOut() { return false; }
		virtual bool IsShop() { return false; }
		virtual bool IsPipe() { return false; }
		virtual bool IsShopGroup() { return false; }
		static bool OBJCMP(BObject *pObject1, BObject *pObject2);

		// Возвращает минимально- и максимально допустимые давления, bOut - на выходе, !bOut - на входе объекта
		virtual bool GetPminMax(double& Pmin, double& Pmax);
		void SetProcessed(bool bProcessed) {m_bProcessed = bProcessed;}
		virtual void Rollback(RRollbackParams *pRollbackStorage = NULL){}
		virtual void StoreParams(RRollbackParams *pRollbackStorage = NULL){}

		// добавляет в сумму величину совершенной работы
		virtual void SummA(double *pA, OptEnums::TypeA type){}

	public:
		bool m_bProcessed;
		bool m_bCalculated; // признак, что для объекта есть расчетные значения
		bool m_bPostCalculated; // признак, что для объект заполнил расчетные значения
		int m_ID;
		int m_NodeStart; // Узел начала
		int m_NodeEnd;	 // Узел конца
		int m_CalculatedEdgesCount; // количество просчитанных ребер (для RShopGroup)

		// Результаты расчета
		double m_rPin; // Давление на входе объекта [ата]
		double m_rTin; // Температура на входе объекта [0С]
		double m_rRo_in; // Относительная плотность газа на входе объекта
		double m_rHin;  // Низшая теплотворная способность газа на входе объекта
		double m_rQin;  // Расход газа на входе объекта [млн.м3/сут]
		double m_rPout; // Давление на выходе объекта [ата]
		double m_rTout; // Температура на выходе объекта [0С]
		double m_rRo_out; // Относительная плотность газа на выходе объекта
		double m_rHout; // Низшая теплотв. Способн. газа на выходе объекта [кДж/м3]
		double m_rQout;	// Расход газа на выходе объекта [млн.м3/сут]

		DMapFile* m_pMap;
	};	
}
