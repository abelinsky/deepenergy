#include "pch.h"
#include "GlobalData.h"
#include <boost/filesystem.hpp>
#include "MaxThroughputTask.h"
#include "SimpleTask.h"

namespace Core
{
	CGlobalData gData;

	void AddAlert(CAlert *pAlert)
	{
		gData.m_AlertsMap[pAlert->m_AlertType].push_back(pAlert);
	}

	void ResetAlerts()
	{
		for (auto i = gData.m_AlertsMap.begin(); i != gData.m_AlertsMap.end(); i++)
		{
			for (auto j = i->second.begin(); j != i->second.end(); j++)
			{
				delete *j;
			}
		}
		gData.m_AlertsMap.clear();
	}

	list<CAlert*>* GetAlerts(OptEnums::AlertType AlertType)
	{
		if (gData.m_AlertsMap.find(AlertType) != gData.m_AlertsMap.end())
			return &gData.m_AlertsMap[AlertType];
		return NULL;
	}

	void DoLogForced(const string& s, bool bReset)
	{
		string outstr = (boost::format("%s: %s\n") % GetCurrentTimeStr() % s).str();

		#ifndef _FORCE_LOGGING_CMD_ONLY
		
		FILE *pLogfile;
		errno_t err = fopen_s(&pLogfile, (gData.m_DataDir + "log.txt").c_str(), "a");
		if (err == 0)
		{
			fprintf(pLogfile, outstr.c_str());
			fclose(pLogfile);
		}

		#endif

		std::cout << outstr.c_str();

	}

	/*
		void DoLog(const string& path, const string& s)
	{
		FILE *pLogfile;
		errno_t err = fopen_s(&pLogfile, (path + "log.txt").c_str(), "a");
		if (err == 0)
		{
			fprintf(pLogfile, "%s: %s\n", GetCurrentTimeStr().c_str(), s.c_str());
			fclose(pLogfile);
		}

		std::cout << GetCurrentTimeStr().c_str() << ": " << s << endl;
	}
	*/

	/* CGlobalData */
	CGlobalData::CGlobalData()
	{
		m_bOptimisation = false;
		m_bControlRestrictions = true;
		m_bVariationsTask = false;
		m_bEnableKSOff = false;
		m_bNoSchemes = true;
		m_bCheckStability = true;
		m_CurrentCriteria = OptEnums::Criterias::C_MaxPout;
		m_nKSEfficiencyFormulas = 0;
		m_bRelativeValues = true;
		m_bShopsOut = false;
		m_bChangeCBN = false;
		m_kKTSGTUQtg = 1;
		m_kKTSForce = 1;
		m_kKeff = 1;
		m_kP = 1;
		m_TMode = OptEnums::TMode::T_Set;
		m_pCurrentTask = NULL;
	}
	
	CGlobalData::~CGlobalData()
	{
		ResetAlerts();

		if (m_pCurrentTask)
			delete m_pCurrentTask;
	}

	string CGlobalData::GetTaskName(CTrainingTask::TaskType Task)
	{
		return Tasks::CTrainingTask::GetTaskName(Task);
	}

	void CGlobalData::SetCurrentTask(CTrainingTask::TaskType Task)
	{
		if (m_pCurrentTask)
			delete m_pCurrentTask;
		m_pCurrentTask = NULL;
		
		switch (Task)
		{
		case CTrainingTask::TaskType::MAX_THROUGHPUT:
			m_pCurrentTask = new CMaxThroughputTask;
			break;
		case CTrainingTask::TaskType::SIMPLE:
			m_pCurrentTask = new CSimpleTask;
			break;
		default:
			break;
		}
		
		assert(m_pCurrentTask);
	}

	void CGlobalData::SetTMode(OptEnums::TMode tMode)
	{
		m_TMode = tMode;
		switch (m_TMode)
		{
		case OptEnums::TMode::T_Calc:
		{
			GetModel()->m_pGTS->m_AVOCalc = -1;
			break;
		}
		//case OptEnums::TMode::T_Set:
		default:
		{
			GetModel()->m_pGTS->m_AVOCalc = 3;
			break;
		}
		};
	}
}