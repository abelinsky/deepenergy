#pragma once

#include "BNSI.h"

namespace NSI
{
	struct KTInterval
	{
		KTInterval()
		{
			m_Tmin = 0.;
			m_Tmax = 0.;
			m_kt = 0.;
			m_T = 0.;
		}
		void operator =(const KTInterval &Source)
		{
			m_Tmin = Source.m_Tmin;
			m_Tmax = Source.m_Tmax;
			m_kt = Source.m_kt;
			m_T = Source.m_T;
		}

		double m_Tmin;		// левое значение температуры
		double m_Tmax;		// правое значение температуры
		double m_kt;		// коэффициент kt
		double m_T;			// условно номинальная температура
	};

	class BNSIGPA : public BNSI
	{
	public:
		BNSIGPA(void);
		virtual ~BNSIGPA(void);
		virtual void LoadData(istream&);
		virtual bool CheckLoadedData(string& Error);
		virtual void PrintExportData(ostream&);

		// копировать параметры ЦБН
		virtual void CopyForceParams(BNSIGPA *pSource);
		// копировать параметры привода
		virtual void CopyDriveParams(BNSIGPA *pSource);

	public:
		// m_ID - Шифр ГПА
		int m_nCharacteristic;		// 1 – есть (мощность и кпд), 2 – есть (ст. сжатия и кпд)
		int m_DriveType;			// признак привода (0-эл.привод/ 1-ГТУ/ 2-ГМК)
		bool m_bWholeHead;			// признак (1-полнонапорный/ 0-нет)
		double m_kNmax;				// Максимально-допустимое отношение расп. мощности к номинальной
		vector <double> m_kN;		// коэффициенты аппроксимации мощностной характеристики
		vector <double> m_kK;		// коэффициенты аппроксимации характеристики политропического КПД
		vector <double> m_kE;		// коэффициенты аппроксимации напорной характеристики
		double m_N;					// номинальная мощность [кВт]
		double m_Qtg;				// номинальный расход топливного газа с учетом тех. сос. [млн.м3/сут]
		double m_H;					// номинальная низшая теплота сгорания [кДж/м3]
		double m_Tair;				// номинальная температура воздуха на входе ГТУ [0С]
		double m_Pair;				// номинальное значение давления воздуха [ата]
		double m_Qmin;				// минимально-допустимый приведенный расход [м3/мин]
		double m_Qmax;				// максимально-допустимый приведенный расход [м3/мин]
		double m_nmin;				// минимально-допустимые относительные обороты
		double m_nmax;				// максимально-допустимые относительные обороты
		double m_dP;				// потери давления между ступенями сжатия  [ата]
		double m_Z;					// коэффициент  сжимаемости приведения
		double m_T;					// температура приведения [0С]
		double m_R;					// газовая постоянная приведения [Дж/кг град]
		double m_wKPD;				// КПД электродвигателя
		double m_mKPD;				// КПД мультипликатора
		double m_kUtil;				// коэффициент  влияния системы утилизации
		double m_mechKPD;			// механический КПД
		vector <KTInterval> m_ktIntervals; // Интервалы коэффициента kt
	};
}