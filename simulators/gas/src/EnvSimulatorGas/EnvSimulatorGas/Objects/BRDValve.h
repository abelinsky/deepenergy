#pragma once

#include "BValve.h"

namespace Objects
{
	class BRDValve : public BValve
	{
	public:
		BRDValve(void);
		virtual ~BRDValve(void);
		virtual void LoadData(istream&);
		virtual bool CheckLoadedData(string& Error);
		virtual int GetMatrixID();
		virtual void PostAdd();
		virtual void PostErased();
		virtual void ClearResults();
		virtual void PrintExportData(ostream&);
		virtual void ImportAdaptation(istream&);		
		virtual void ExportAdaptation(ostream&);
	
	public:
		int m_Type;			// Тип крана (0 – регулятор или дросель, 1 – постоянный дроссель или байпасный кран)
		double m_Pinmin;	// Минимально допустимое давление газа перед краном [ата]
		double m_Poutmax;	// Максимально допустимое давление газа на выходе крана [ата]
		double m_Pset;		// Уставка давления газа на выходе регулятора [ата]
		double m_DWhole;	// Диаметр полностью открытого крана [мм]
		double m_d;			// Условный диаметр крана [мм]
		double m_k;			// Коэф.местных сопротивлений крана

		// Результаты расчета
		double m_rd;			// Условный диаметр крана [мм]
		double m_rk;			// Коэф.местных сопротивлений крана
	};
}