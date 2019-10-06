#pragma once


namespace Objects
{
	class BManagedObject;
	// Разрешенные управления
	enum OParam
	{
		O_OB = 1,    // Обороты ГПА
		O_SCHOB = 2, // Схемы работы ГПА
		O_ORD = 3,   // Процент открытия кранов РД
		O_E = 4,     // Степень сжатия ГПА, КЦ и т.д.
		O_T = 5      // Температура выхода КЦ (групп КЦ)
	};

	inline string GetParamDescription(OParam param) {
		switch (param)
		{
		case O_E:
			return "Compression ratio";
		case O_T:
			return "Temperature";
		default:
			return "Not defined";
		}
	}

	// Класс управляемого параметра, управления - непрерывные (double)
	class RManagedParam
	{
	public:
		RManagedParam(BManagedObject* pParent, double* pParam, OParam Code);
		virtual ~RManagedParam();
		// возвращает границы регулирования
		void GetParamBorders(double &min, double &max);
		double Get();
		string GetUId();
		string GetInfo();
		void Set(double Value);
		//void Rollback();
		void Off();
		void On();
		double GetDelta(); // шаг для расчета производных
		void PostCreate();
		bool IsDiscrete();

	public:
		// string m_uuId; // unique identifier

		BManagedObject* m_pParent;
		double* m_pParam;
		OParam m_Code;
		double m_OldValue;
	};

	typedef Objects::RManagedParam OptimizationParam;
}