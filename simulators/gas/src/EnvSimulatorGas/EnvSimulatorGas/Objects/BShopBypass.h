#pragma once

#include "BShopObject.h"

namespace Objects
{
	class BShopBypass : public BShopObject
	{
	public:
		BShopBypass(void);
		virtual ~BShopBypass(void);
		virtual void LoadData(istream&);
		virtual bool CheckLoadedData(string& Error);
		virtual void PrintExportData(ostream&);
		virtual void PostAdd();
		virtual void PostErased();
	
	public:
		int m_Number;			// Индивидуальный номер крана в КЦ
		int m_Type;				// Тип крана 0-регулятор, 1-байпас
		int m_ConnectionType;	// Тип включения крана в обвязку КЦ 0-вход крана до АВО, 1-после АВО
		double m_DWhole;		// Диаметр полностью открытого крана [мм]
		double m_d;				// Условный диаметр крана [мм] (если тип крана - байпас, то должен совпадать с диаметром полностью открытого крана).
//		int m_oParam;			// Если этот параметр равен нулю (для задачи оптимизации), то считаем, что разрешен режим байпасирования. 
								// При этом, для регулятора определяется степень открытия крана, а для байпаса - открыт или закрыт
		double m_k;				// Коэф. сопротивления крана
	};
}