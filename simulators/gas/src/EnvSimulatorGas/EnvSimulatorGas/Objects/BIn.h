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
		int m_Node; // узел схемы
		double m_P;
		double m_Q;
		double m_T;
		double m_Ro;
		double m_N2;
		double m_C02;
		double m_H;

		// Результаты расчета
		double m_rP;	//Давление в узле [ата]
		double m_rT;	//Температура [0С]
		double m_rRo;	//Относительная плотность газа
		double m_rH;	//Низшая теплотворная способность газа на входе объекта []
		double m_rQ;	//Расход газа [млн.м3/сут]
		double m_rCO2;	//%СО2
		double m_rN2;	//%N2
	};

	class BInOut
	{
	public:
		static bool LoadData(istream&, string& Error);
	};
}