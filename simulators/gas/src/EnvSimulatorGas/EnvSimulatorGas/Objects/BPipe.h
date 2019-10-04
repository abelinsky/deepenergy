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
		int m_Type;				// Тип трубы (0 – магистраль, 2 – отвод, 3 – дюкер или лупинг, 7 - труба обвязки КЦ)
		int m_Thread;			// Номер нитки МГ
		double m_Kef;			// Гидравлическая эффективность
		double m_Kto;			// Коэф. теплопередачи от газа в окружающую среду [вт/(м2 град)]
		double m_T;				// Температура окружающей среды [0С]
		double m_Pmin;			// Минимально допустимое давление газа в трубе [ата]
		double m_Pmax;			// Максимально допустимое давление газа в трубе [ата]
		double m_d;				// Внутренний диаметр трубы [мм]
		double m_D;				// Наружный диаметр трубы [мм]
		double m_L;				// Длина трубы [км]
		double m_k;				// Коэф. шерох-ти трубы [мм]
		double m_dh;			// Разность высот [м]

		// Результаты расчета
		double m_rVin;			// Скорость потока на входе
		double m_rVout;			// Скорость потока на выходе
		double m_rQv;			// Запас газа в трубе (млн.м3)
		double m_rDirection;	// Признак напр.потока(труба)1-не изм./0
	};
}