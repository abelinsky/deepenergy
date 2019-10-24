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
		void SetTMode(OptEnums::TMode tMode); // ������ ������� ������� ���		

	public:

		Mode m_Mode;

		CObjectsModel m_Model;
		CTrainingTask* m_pCurrentTask;
		//OptEnums::Tasks m_CurrentTask;
		OptEnums::TMode m_TMode; // ������� ������� ���
		unordered_map<AlertType, list<CAlert*>> m_AlertsMap;

		OptEnums::Criterias m_CurrentCriteria;
		string m_DataDir;
		bool m_bOptimisation;
		bool m_bControlRestrictions; // �������, �������� �� ����������� �� �������� �������� �� �� � ��
		BOOL m_bVariationsTask; // �������� �������� ����� ���
		BOOL m_bEnableKSOff; // �������, ��������� �� ��������� ��
		BOOL m_bNoSchemes; // �������, ��������� �� ������ ������� �������� ������ ��
		int m_Deviation; // ���������� ������� ������������� ������������� �� (%)
		BOOL m_bCheckStability; // �������, ��������� �� ������������ ������
		int m_nKSEfficiencyFormulas; // ������� ��������� ������ �������� ������������� ��
									// 0 - ������������	
									// 1 - ���������������
		BOOL m_bShopsOut;		// ������ ������� � ������� �� �� ������
		BOOL m_bRelativeValues; // ������������� �������� ������� (��� ����� ������� �������������� ������������)
		BOOL m_bChangeCBN;	// �������, ��� �������� ��� � �������� �������
		string m_CBNFilePath;	// ���� �� ����� � ���������, � ����� �� � ��� ������ ���
		double m_kKTSGTUQtg;	// �������� ��������� ��� ��� �� ���������� ����, % (0.99, 1.02 � �.�.)
		double m_kKTSForce;		// �������� ��������� ��� ��� �� ���������������� �.�.�., % (0.99, 1.02 � �.�.)
		double m_kKeff;	// �������� ��������� ����. �������� �����, % (0.99, 1.02 � �.�.)
		double m_kP; // �������� �������� ������� ��������, ��������� � P��
	};

	extern CGlobalData gData;
	inline CObjectsModel* GetModel() { return &gData.m_Model; }

	void AddAlert(CAlert *pAlert);
	void ResetAlerts();
	list<CAlert*>* GetAlerts(OptEnums::AlertType AlertType);

	void DoLogForced(const string& s, bool bReset = false);
}