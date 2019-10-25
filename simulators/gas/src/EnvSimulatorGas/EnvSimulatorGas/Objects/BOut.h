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
		virtual void ResultsToObject(); // экспорт результатов расчетов в параметры потребителя
		virtual void SummA(double *pA, OptEnums::TypeA type);

		void ExportDynamicsData() override;

	public:
		int m_Node; // узел схемы
		int m_nThread; // идентификатор нитки
		double m_P;
		double m_Q;
		int m_Type;		// Type: 0-обычный отвод/приток, 
						// 1- фиктивный отбор служит для задания опорного давления газа в узле,  
						// 2 – отвод отключен, но в нестац. режиме может быть включен,
						// 3 – фиктивный отвод служит для резки ТС и задания P и Т)

		// Результаты расчета
		double m_rP;	//Давление в узле [ата]
		double m_rT;	//Температура [0С]
		double m_rRo;	//Относительная плотность газа
		double m_rH;	//Низшая теплотворная способность газа на входе объекта []
		double m_rQ;	//Расход газа [млн.м3/сут]
		double m_rCO2;	//%СО2
		double m_rN2;	//%N2
		double m_Pmin;  // Минимальное давление на входе ГРС
	};
}




