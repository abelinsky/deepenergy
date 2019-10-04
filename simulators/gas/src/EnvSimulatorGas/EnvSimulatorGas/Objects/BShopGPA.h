#pragma once

#include "BShopObject.h"

namespace NSI
{
	class BNSI;
	class BNSIGPA;
}

namespace Objects
{
	class BShopGPA : public BShopObject
	{
	public:
		BShopGPA(void);
		virtual ~BShopGPA(void);
		virtual int GetMatrixID();
		virtual void LoadData(istream&);
		virtual bool CheckLoadedData(string& Error);
		virtual void PrintExportData(ostream&);
		virtual void PostAdd();
		virtual void PostErased();
		virtual void ClearResults();
		void InputShopResults(istream&);
		void ExportShopResults(ostream&);
		void ResultsToObject(); // экспорт результатов расчетов в параметры ГПА
		virtual void CheckResults();
		virtual double GetParamDelta(RManagedParam*);
		virtual void GetManagedParamBorders(RManagedParam*, double &min, double &max);

	public:
		BNSIGPA* m_pNSIGPA;

	public:
		int m_Number;			// Индивидуальный номер ГПА в КЦ
		int m_NSIID;			// Идентификатор типа ГПА (шифр НСИ)
		double m_KTSGTU_N;		// Коэф. технического состояния ГПА (ГТУ) по мощности
		double m_KUDmin;		// Коэф., определяющий минимально-допустимую удаленность от зоны помпажа
		double m_KNmax;			// Коэф., определяющий максимально-допустимую загрузку ГПА по мощности
		double m_n;				// Относительные обороты ГПА
		double m_nmin;			// Минимально-допустимые относительные обороты *****
		double m_nmax;			// Максимально-допустимые относительные обороты *****
		double m_Emin;			// Минимально-допустимая степень сжатия *****
		double m_Emax;			// Максимально-допустимая степень сжатия *****
		double m_wtime;			// Время наработки ГПА [тыс.час]
		bool m_bUtilisation;	// Признак наличия системы утилизации тепла
		bool m_bRegeneration;	// Признак наличия системы регенерации 
		bool m_bAntiIceSystem;	// Признак наличия противообледенительной системы
		int m_StageAllowed;		// Разреш. Ступень подключ. (0 – любая, 1- в первую, 2 – во вторую, 3- ГПА работает в 1-ю ступень при условии наличия второй ступени) *
		double m_KTSQtg;		// Коэф. технического состояния ГТУ по топливному газу
		double m_KTSCBN_N;		// Коэф. технического состояния ЦБН по мощности
		double m_KTS_K;			// Коэф. технического состояния ЦБН по кпд
		double m_KTS_MK;		// Коэф. технического состояния по мех.кпд
		int m_State;			// Состояние, 0 - отключен, 1 - работает

		// Результаты расчета
		double m_rg_n;			// Относительные обороты
		double m_rgKpol;		// Политропический КПД
		double m_rgPin;			// Давление на входе [ата]
		double m_rgTin;			// Температура на входе [0С]
		double m_rgE;			// Степень сжатия
		double m_rgPout;		// Давление на выходе [ата]
		double m_rgTout;		// Температура на выходе [0С]
		double m_rgQcomm;		// Коммерческий расход газа [млн.м3/сут]
		double m_rgQtg;			// Расход топливного газа [млн.м3/сут]
		double m_rgQ;			// Объемный приведенный расход газа [м3/мин]
		double m_rgKpom;		// Коэф. удаленности от зоны помпажа 
		double m_rgW;			// Расход электроэнергии  [кВт/час]
		double m_rgN;			// Мощность, потреб-мая нагн. [кВт]
		double m_rgNres;		// Резерв мощности  [кВт]
		double m_rgKz;			// Коэф. загрузки ГПА
	};
}
