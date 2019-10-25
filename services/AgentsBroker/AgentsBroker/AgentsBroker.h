
// AgentsBroker.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAgentsBrokerApp:
// See AgentsBroker.cpp for the implementation of this class
//

class CAgentsBrokerApp : public CWinApp
{
public:
	CAgentsBrokerApp();

	bool StartTraining();
	bool StartServing();

protected:
	HANDLE StartSimulationService();
	HANDLE StartTrainingService();
	HANDLE StartTensorBoard();

	HANDLE StartServingService();
	
protected:
	CString m_IniPath;
	CString m_FullDataPath;
	CString m_LocalDataDir;
	CString m_SimulationService;
	CString m_PythonInterpreter;
	CString m_TrainingScript;
	CString m_PredictorService;

	CString GetServingServiceCmdParams();
	CString GetSimulationServiceCmdParams();
	CString GetTrainingServiceCmdParams();

private:
	HANDLE m_hSimulationProcess;
	HANDLE m_hTrainingProcess;
	HANDLE m_hTensorBoardProcess;

	HANDLE m_hServingProcess;

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CAgentsBrokerApp theApp;
