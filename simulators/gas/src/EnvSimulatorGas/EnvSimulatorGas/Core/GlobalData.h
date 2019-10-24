#pragma once

#include "OptEnums.h"
#include "ObjectsModel.h"
#include "TrainingTask.h"

#undef _DOLOGGING

#ifndef _FORCE_LOGGING_CMD_ONLY
#define _FORCE_LOGGING_CMD_ONLY
#endif

#ifndef _DOLOGGING
#define DoLog(x) ((void)0)
#else
#define DoLog(x) DoLogForced(x)
#endif

#ifndef _FORCE_DISCRETE_ACTIONS
#define _FORCE_DISCRETE_ACTIONS
#endif

constexpr auto EXPERIMENT = 2;

namespace Core 
{
	enum Mode
	{
		TRAINING_SERVICE,
		RECOMMENDATION_SERVICE
	};

	class CAlert
	{
	public:
		CAlert(BObject* pObject, string sAlert, OptEnums::AlertType AlertType)
		{
			m_pObject = pObject;
			m_sAlert = sAlert;
			m_AlertType = AlertType;
		}
		~CAlert(void) {}
		BObject* m_pObject;
		string m_sAlert;
		OptEnums::AlertType m_AlertType;
	};

	class CGlobalData
	{
	public:
		CGlobalData();
		~CGlobalData();
		
		string GetTaskName(CTrainingTask::TaskType);
		inline CTrainingTask* GetCurrentTask() { return m_pCurrentTask; }
		void SetCurrentTask(CTrainingTask::TaskType);
		void SetTMode(OptEnums::TMode tMode); // задать признак расчета АВО		

	public:

		Mode m_Mode;

		CObjectsModel m_Model;
		CTrainingTask* m_pCurrentTask;
		//OptEnums::Tasks m_CurrentTask;
		OptEnums::TMode m_TMode; // признак расчета АВО
		unordered_map<AlertType, list<CAlert*>> m_AlertsMap;

		OptEnums::Criterias m_CurrentCriteria;
		string m_DataDir;
		bool m_bOptimisation;
		bool m_bControlRestrictions; // Признак, задавать ли ограничения по рабочему давлению на КЦ и ЛЧ
		BOOL m_bVariationsTask; // вариации расходов через ГТС
		BOOL m_bEnableKSOff; // признак, разрешать ли выключать КС
		BOOL m_bNoSchemes; // признак, вычислять ли только уставки степеней сжатия КС
		int m_Deviation; // допустимый разброс коэффициентов эффективности КС (%)
		BOOL m_bCheckStability; // признак, проверять ли устойчивость режима
		int m_nKSEfficiencyFormulas; // признак расчетных формул удельной эффективности КС
									// 0 - квадратичные	
									// 1 - логарифмические
		BOOL m_bShopsOut;		// Полный перебор с выводом КЦ на проход
		BOOL m_bRelativeValues; // относительные приросты величин (для задач расчета функциональных зависимостей)
		BOOL m_bChangeCBN;	// признак, что заменять СПЧ в процессе расчета
		string m_CBNFilePath;	// путь до файла с указанием, в каких КЦ у ГПА менять СПЧ
		double m_kKTSGTUQtg;	// имитация изменения КТС ГТУ по топливному газу, % (0.99, 1.02 и т.д.)
		double m_kKTSForce;		// имитация изменения КТС ЦБН по политропическому к.п.д., % (0.99, 1.02 и т.д.)
		double m_kKeff;	// имитация изменения Кэфф. линейной части, % (0.99, 1.02 и т.д.)
		double m_kP; // имитация снижения входных давлений, множитель к Pвх
	};

	extern CGlobalData gData;
	inline CObjectsModel* GetModel() { return &gData.m_Model; }

	void AddAlert(CAlert *pAlert);
	void ResetAlerts();
	list<CAlert*>* GetAlerts(OptEnums::AlertType AlertType);

	void DoLogForced(const string& s, bool bReset = false);
}