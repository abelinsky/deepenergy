#pragma once
#include "BObject.h"

namespace Objects
{
	class BGTS : public BObject
	{
	public:
		BGTS(void);
		virtual ~BGTS(void);
		virtual void LoadData(istream&);
		virtual void PostAdd();
		virtual void PostErased();
		virtual void PrintExportData(ostream&);
	
	public:
		double m_kNmax;					// Nрасп/Nном <=
		bool m_bControlKcharge;			// Контроль Кзагр (ГПА)
		double m_TairAdd;				// Поправка на Tвоз
		double m_TAVO;					// Поправка на на изменчивость климатических параметров (расчет АВО)
		int m_AVOCalc;					// Признак расчета АВО
										// -1 – прямой расчет АВО или сброс на выходе КЦ температуры на dT АВО
										// 2 – обеспечение уставки выходной температуры  (или если заданы параметры станции АВО расчет кол-ва АВО и вентиляторов, обеспечивающие Твых)
										// если в LimitationsGTS.dat задать параметр равный 3, а в CompressorShop.dat на месте dT АВО задать, например, 40, то Салс будет на выходе КЦ выдерживать Твых=40
										// если  в файле LimitationsGTS.dat параметр "признак расчета АВО" задавать равный 2, то как для КЦ (CompressorShop.dat), так и для потоковой модели (Lost.dat) задается уставка выходной температуры, если "признак расчета АВО" равен 1, то задается dT.
		double m_Pdrift;				// Погрешность по P
		double m_Qvalidity;				// Точность по Qузл
		double m_Qdrift;				// Погрешность по Q
		bool m_bControlKud;				// Контроль Куд (ГПА)
		int m_OptimizationCriteria;		// Критерий оптимизации КЦ
										// 0 - энергозатраты
										// 1 - топливный газ
										// 2 - электроэнергия
										// 3 - стоимостные затраты
		int m_PipesCollapse;			// Эквивалентирование (Нет, да, глубокое эквивалентирование)
		bool m_bIntershopsIgnore;		// Игнорировать трубы обвязки КЦ
		int m_GroupGRS;					// Признак группировки кустов ГРС
		int m_nPointsMax;				// Количество точек разбиения
		int m_FormulasType;				// Формулы ОНТП
		bool m_bKvaziDisable;			// Запретить квазистационар
	};
}