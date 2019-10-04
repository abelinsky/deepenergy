#pragma once

#include "BNSI.h"

namespace NSI
{
	class BNSIAVO : public BNSI
	{
	public:
		BNSIAVO(void);
		virtual ~BNSIAVO(void);
		virtual void LoadData(istream&);
		virtual bool CheckLoadedData(string& Error);
		virtual void PrintExportData(ostream&);

	public:
		// m_ID - Шифр АВО
		string m_Name;			// Название АВО
		int m_PipesCount;		// Количество труб в АВО (паспорт)
		int m_StepsCount;		// Количество ходов газа по трубам в АВО  (входит в структуру условного обозначения АВО)
		int m_VentCount;		// Количество вентиляторов в АВО (паспорт)
		double m_kFinning;		// Коэффициент оребрения (входит в структуру условного обозначения АВО)
		double m_PipesLength;	// Длина труб (входит в структуру условного обозначения АВО) [м]
		double m_Sout;			// Поверхность теплообмена наружная (по оребрению) (паспорт) АВО [м2]
		double m_Sin;			// Поверхность теплообмена внутренняя АВО (паспорт)  [м2]
		double m_Scutset;		// Площадь поперечного сечения прохождения воздуха  (паспорт) [м2]
		double m_kTaper;		// Коэффициент сужения
		double m_C;				// Эквивалентная теплопроводность материала стенок трубы и контактной поверхности [вт/(м . K)]
		double m_QVent;			// Производительность вентилятора [тыс м3/ч] 
		double m_l;				// Шаг между ребрами [мм]
		double m_h;				// Высота ребра  [мм]
		double m_w;				// Средняя толщина ребра [мм]
		double m_k;				// Поправочный коэффициент, учитывающий вид оребрения, эффективность ребра и т.п.
		double m_N;				// Мощность электродвигателя на валу [кВт]
	};
}