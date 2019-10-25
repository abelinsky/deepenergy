
// AgentsBroker.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AgentsBroker.h"
#include "AgentsBrokerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAgentsBrokerApp

BEGIN_MESSAGE_MAP(CAgentsBrokerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()



CAgentsBrokerApp::CAgentsBrokerApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	m_hSimulationProcess = nullptr;
	m_hTrainingProcess = nullptr;
	m_hTensorBoardProcess = nullptr;
	m_hServingProcess = nullptr;
}

// The one and only CAgentsBrokerApp object

CAgentsBrokerApp theApp;


// CAgentsBrokerApp initialization

bool CAgentsBrokerApp::StartTraining()
{
	fs::path localDataPath(fs::path(m_SimulationService.GetString()).parent_path() / fs::path(m_LocalDataDir.GetString()));
	if (fs::is_directory(localDataPath))
		fs::remove_all(localDataPath);
	fs::create_directory(localDataPath);

	// copy files from initial data location to local location
	fs::copy(fs::path(m_FullDataPath.GetString()), localDataPath);

	m_hSimulationProcess = StartSimulationService();
	if (!m_hSimulationProcess)
	{
		AfxMessageBox("Failed to start simulation service.");
		return false;
	}

	m_hTrainingProcess = StartTrainingService();
	if (!m_hTrainingProcess)
	{
		AfxMessageBox("Failed to start training.");
		return false;
	}
	return true;
}

bool CAgentsBrokerApp::StartServing()
{
	m_hServingProcess = StartServingService();
	if (!m_hServingProcess)
	{
		AfxMessageBox("Failed to start serving service.");
		return false;
	}
	return true;
}

BOOL CAgentsBrokerApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("ab"));

	char buff[MAX_PATH];
	GetModuleFileName(AfxGetInstanceHandle(), buff, MAX_PATH);
	CString appPath = buff;
	int n = appPath.ReverseFind('\\');
	if (n != -1)
		appPath = appPath.Left(n + 1);

	m_IniPath.Format("%s\\%s", appPath, "AgentsBroker.ini");
	
	CStringArray cmdParams;
	for (int i = 1; i < __argc; i++)
	{
		LPCTSTR pszParam = __targv[i];
		if (pszParam[0] == '-' || pszParam[0] == '/')
		{
			++pszParam;
		}
		cmdParams.Add(pszParam);

		// AfxMessageBox(_T(pszParam));
	}

#ifdef _DEBUG
	SetCurrentDirectory("C:\\Users\\ab\\AppData\\Roaming\\Vesta\\");
	cmdParams.Add("106");
	cmdParams.Add("Data\\");
#endif

	if (cmdParams.GetCount() != 2)
	{
		AfxMessageBox(_T("Ќеверно заданы параметры командной строки:\n"));
		return FALSE;
	}

	// Read inin params

	TCHAR currentDir[MAX_PATH];
	GetCurrentDirectory(sizeof(currentDir), currentDir);
	m_FullDataPath.Format("%s\\%s", currentDir, cmdParams[1]);

	TCHAR buffer[MAX_PATH];
	GetPrivateProfileString("setup", "SimulationService", NULL, buffer, sizeof(buffer), m_IniPath);
	m_SimulationService = buffer;

	GetPrivateProfileString("setup", "PythonInterpreter", NULL, buffer, sizeof(buffer), m_IniPath);
	m_PythonInterpreter = buffer;

	GetPrivateProfileString("setup", "TrainingScript", NULL, buffer, sizeof(buffer), m_IniPath);
	m_TrainingScript = buffer;

	GetPrivateProfileString("setup", "LocalSimulationDataDir", NULL, buffer, sizeof(buffer), m_IniPath);
	m_LocalDataDir = buffer;

	GetPrivateProfileString("setup", "PredictorService", NULL, buffer, sizeof(buffer), m_IniPath);
	m_PredictorService = buffer;

	int task = atoi(cmdParams[0]);
	switch (task) // task
	{
	case 1: // forward calc of regime
		break;
	case 101: // serve model
		if (!StartServing())
			return FALSE;
		break;
	case 106: // AI training
		if (!StartTraining())
			return FALSE;
		break;
	}

	CAgentsBrokerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

CString CAgentsBrokerApp::GetSimulationServiceCmdParams()
{
	CString params;
	params.Format("%s", m_SimulationService);
	return m_SimulationService;
}

CString CAgentsBrokerApp::GetTrainingServiceCmdParams()
{
	CString params;
	params.Format("%s -i %s --data %s", m_PythonInterpreter, m_TrainingScript, m_LocalDataDir);
	return params;
}

CString CAgentsBrokerApp::GetServingServiceCmdParams()
{
	CString params;
	params.Format("%s serve %s", m_PredictorService, m_FullDataPath);
	return params;
}

HANDLE CAgentsBrokerApp::StartSimulationService()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_NORMAL;
	if (!CreateProcess(NULL, GetSimulationServiceCmdParams().GetBuffer(_MAX_PATH * 2), 
		NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) // CREATE_NO_WINDOW
		return NULL;
	CloseHandle(pi.hThread);
	WaitForInputIdle(pi.hProcess, INFINITE);
	return pi.hProcess;
}

HANDLE CAgentsBrokerApp::StartTrainingService()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	if (!CreateProcess(NULL, GetTrainingServiceCmdParams().GetBuffer(_MAX_PATH * 2), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
		return NULL;
	CloseHandle(pi.hThread);
	WaitForInputIdle(pi.hProcess, INFINITE);
	return pi.hProcess;
}

HANDLE CAgentsBrokerApp::StartServingService()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	if (!CreateProcess(NULL, GetServingServiceCmdParams().GetBuffer(_MAX_PATH * 2), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
		return NULL;
	CloseHandle(pi.hThread);
	WaitForInputIdle(pi.hProcess, INFINITE);
	return pi.hProcess;
}

int CAgentsBrokerApp::ExitInstance()
{
	if (m_hTrainingProcess)
	{
		DWORD dwExitCode;
		GetExitCodeProcess(m_hTrainingProcess, &dwExitCode);
		if (dwExitCode == STILL_ACTIVE)
		{
			TerminateProcess(m_hTrainingProcess, 0);
		}
	}

	if (m_hSimulationProcess)
	{
		DWORD dwExitCode;
		GetExitCodeProcess(m_hSimulationProcess, &dwExitCode);
		if (dwExitCode == STILL_ACTIVE)
		{
			TerminateProcess(m_hSimulationProcess, 0);
		}
	}

	if (m_hTensorBoardProcess)
	{
		DWORD dwExitCode;
		GetExitCodeProcess(m_hSimulationProcess, &dwExitCode);
		if (dwExitCode == STILL_ACTIVE)
		{
			TerminateProcess(m_hSimulationProcess, 0);
		}
	}

	m_hTrainingProcess = NULL;
	m_hSimulationProcess = NULL;
	m_hTensorBoardProcess = NULL;

	return CWinApp::ExitInstance();
}

HANDLE CAgentsBrokerApp::StartTensorBoard()
{
	TCHAR buffer[MAX_PATH*2];
	GetPrivateProfileString("setup", "TensorBoardService", NULL, buffer, sizeof(buffer), m_IniPath);
	CString tensorBoardPath = buffer;

	GetPrivateProfileString("setup", "TensorBoardData", NULL, buffer, sizeof(buffer), m_IniPath);
	CString tensorBoardData = buffer;

	CString params;
	params.Format("%s --logdir %s", tensorBoardPath, tensorBoardData);
	// AfxBeginThread(ExternThread, &params);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_NORMAL;
	if (!CreateProcess(NULL, params.GetBuffer(_MAX_PATH * 2),
		NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) // CREATE_NO_WINDOW
		return NULL;
	CloseHandle(pi.hThread);
	WaitForInputIdle(pi.hProcess, INFINITE);
	return pi.hProcess;
}