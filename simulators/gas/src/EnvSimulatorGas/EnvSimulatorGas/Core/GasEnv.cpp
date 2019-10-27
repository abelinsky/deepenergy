#include "pch.h"
#include "GasEnv.h"
#include <time.h>
#include "utils.h"
#include "FileSystem.h"
#include "BShopGPA.h"
#include "BIn.h"

#include <grpcpp/grpcpp.h>
#include "energyplatform/core/predictor_service.grpc.pb.h"
#include "ServerMapper.h"
using namespace SimulationServer;

namespace Core
{
	CGasEnv::CGasEnv()
	{
		m_hCalcProcess = NULL;
		
		m_hDynRunEvent_calc = CreateEvent(NULL, true, false, "VestaDynRun");
		m_hDynConfirmEvent_calc = CreateEvent(NULL, true, false, "VestaDynConfirm");

		m_hServingRunEvent = CreateEvent(NULL, true, false, "AIDynRun");
		m_hServingConfirmEvent = CreateEvent(NULL, true, false, "AIDynConfirm");
		m_hServingForceCloseEvent = CreateEvent(NULL, false, false, "AIForceClose");
	}

	CGasEnv::~CGasEnv()
	{
		StopSimulations();
		CloseHandle(m_hDynRunEvent_calc);
		CloseHandle(m_hDynConfirmEvent_calc);
		
		CloseHandle(m_hServingRunEvent);
		CloseHandle(m_hServingConfirmEvent);
		CloseHandle(m_hServingForceCloseEvent);
	}

	void CGasEnv::ResetCalcEvents()
	{
		ResetEvent(m_hDynRunEvent_calc);
		ResetEvent(m_hDynConfirmEvent_calc);
	}

	HANDLE CGasEnv::StartSimulator(const string& processParams)
	{
		m_hCalcProcess = NULL;
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE; // TODO: SW_SHOWMINNOACTIVE
		string cmdInfo = "Calc.dll " + processParams;
		if (!CreateProcess(NULL, const_cast<char*>(cmdInfo.c_str()), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
			return NULL;
		CloseHandle(pi.hThread);
		m_hCalcProcess = pi.hProcess;
		WaitForInputIdle(m_hCalcProcess, INFINITE);
		return m_hCalcProcess;
	}

	void CGasEnv::StopSimulations()
	{
		if (m_hCalcProcess)
		{
			DWORD dwExitCode;
			GetExitCodeProcess(m_hCalcProcess, &dwExitCode);
			if (dwExitCode == STILL_ACTIVE)
			{
				TerminateProcess(m_hCalcProcess, 0);
			}
		}
		m_hCalcProcess = NULL;
		m_SimulatorData.m_lpEvents[0] = NULL;
		m_SimulatorData.m_lpEvents[1] = NULL;

		DoLog("Simulator stopped");
	}

	bool CGasEnv::DoSimulation(HANDLE lpEvents[2], const string& ProcessParams, const string& DataDir)
	{
		ClearErrorFiles(m_SimulatorData.m_DataDir);
		ClearResultFiles(m_SimulatorData.m_DataDir);
		ResetCalcEvents();

		DWORD dwCode = 1;
		if (!m_SimulatorData.m_lpEvents[1]) // hProcess
		{
			DoLog("Trying to start virtual simulator...");
			ResetCalcEvents();
			// CObjectsModel *pModel = m_ThreadData.m_pModel;
			m_SimulatorData.m_ProcessParams = "116 " + m_SimulatorData.m_DataDir;
			HANDLE hProcess = StartSimulator(m_SimulatorData.m_ProcessParams);
			if (!hProcess)
			{
				DoLogForced("Can't find simulator Calc.dll");
				return false;
			}
			DoLog("Simulator started");

			m_SimulatorData.m_lpEvents[0] = m_hDynConfirmEvent_calc;
			m_SimulatorData.m_lpEvents[1] = hProcess;
			dwCode = WaitForMultipleObjects(2, m_SimulatorData.m_lpEvents, false, INFINITE);
		}
		else
		{
			SetEvent(m_hDynRunEvent_calc);
			dwCode = (WaitForMultipleObjects(2, lpEvents, false, INFINITE) - WAIT_OBJECT_0);
		}

		ResetCalcEvents();
		if (dwCode == 1)
		{
			StopSimulations();
			return false;
		}
		DWORD dwExitCode;
		GetExitCodeProcess(lpEvents[1], &dwExitCode);
		if ((dwExitCode != STILL_ACTIVE) ||
			(dwExitCode == EXCEPTION_BREAKPOINT)
			)
		{
			StopSimulations();
			HANDLE hProcess = StartSimulator(ProcessParams);
			lpEvents[1] = hProcess;
			WaitForMultipleObjects(2, lpEvents, false, INFINITE);
		}

		return true;
	}

	void CGasEnv::ClearErrorFiles(const string &DataDir)
	{
		CFileSystem fs;
		fs.Remove((DataDir + "Error.dat").c_str());
		fs.Remove((DataDir + "Balance.dat").c_str());
	}

	void CGasEnv::ClearResultFiles(const string &DataDir)
	{
		CFileSystem fs;
		fs.Remove((DataDir + "Result.dat").c_str());
		fs.Remove((DataDir + "ResultCompressorShop.dat").c_str());
		fs.Remove((DataDir + "ResultCraneIdent.dat").c_str());
	}

	void CGasEnv::ExportShopData(const string& DataDir)
	{
		CObjectsModel *pModel = GetModel();
		CFileSystem fs;
		fs.CleanFile(DataDir + "CompressorShop.dat");
		ofstream ShopOut;
		ShopOut.open(DataDir + "CompressorShop.dat");
		// ���������� �� ��
		{
			int nCount = pModel->m_Shops.size();
			ShopOut << nCount << endl;
			for (vector <BObject*>::iterator i = pModel->m_Shops.begin(); i != pModel->m_Shops.end(); i++)
			{
				BObject *pObject = *i;
				pObject->PrintExportData(ShopOut);
				ShopOut << endl;
			}
		}
		ShopOut.flush();
		ShopOut.close();
	}

	void CGasEnv::ExportOperativeShopData(const string &DataDir, bool bExportAll)
	{
		CObjectsModel *pModel = GetModel();
		string sCompressorOpt = DataDir + "CompressorOpt.dat";
		string sLostOpt = DataDir + "LostOpt.dat";
		string sControl = DataDir + "Control.dat";

		CFileSystem fs;
		fs.CleanFile(sControl);
		fs.CleanFile(sLostOpt);
		fs.CleanFile(sCompressorOpt);

		if (bExportAll || pModel->m_bSchemeChanged)
			pModel->ExportData(DataDir);

		// ������� ���������� �� ��	
		if (GetModel()->m_bSchemeChanged)
		{
			ofstream ControlOut;
			ControlOut.open(sControl);
			ControlOut.close();
			pModel->m_bSchemeChanged = false;
			fs.CleanFile(sLostOpt);
			fs.CleanFile(sCompressorOpt);
		}
		else
		{
			ofstream ShopOut, LostOut;
			ShopOut.open(sCompressorOpt);
			LostOut.open(sLostOpt);
			for_each(pModel->m_ParallelShops.begin(), pModel->m_ParallelShops.end(), bind(&BObject::InitForExport, _1));
			int nCount = pModel->m_Shops.size();
			ShopOut << nCount << endl;
			LostOut << pModel->CountGroupLosts() << endl;
			for (vector <RShopsGroup*>::iterator i = pModel->m_ParallelShops.begin(); i != pModel->m_ParallelShops.end(); i++)
			{
				RShopsGroup *pGroup = *i;
				if (pGroup->CanExport())
				{
					double T = pGroup->m_rTout;
					if ((pGroup->m_dE > 1.01) && (gData.m_TMode == OptEnums::TMode::T_Set))
						T = pGroup->m_setTout;
					LostOut << pGroup->m_ID << " " <<
						pGroup->m_dE << " " << T << " " << pGroup->m_dQ << endl;
				}
			}
			for (vector <BObject*>::iterator i = pModel->m_Shops.begin(); i != pModel->m_Shops.end(); i++)
			{
				(*i)->PrintExportData(ShopOut);
			}
			LostOut.flush();
			LostOut.close();
			ShopOut.flush();
			ShopOut.close();
		}
	}

	void CGasEnv::ExportOperativeData(const string& DataDir, bool bExportAll)
	{
		ExportOperativeShopData(DataDir, bExportAll);
	}

	// =================== Public methods =============================/

	bool CGasEnv::LoadData(const string& FullPath)
	{
		gData.m_DataDir = FullPath;
		m_SimulatorData.m_InitialDir = FullPath;

		string Errors, Warnings;

		if (!GetModel()->LoadData(gData.m_DataDir, Errors, Warnings))
		{
			DoLogForced("Data path doesn't contain appropriate dataset.");
			DoLogForced("(" + gData.m_DataDir + ")");
			if (!Errors.empty())
				DoLogForced("Errors: " + Errors);
			if (!Warnings.empty())
				DoLogForced("Warnings: " + Warnings);
			return false;
		}

		CFileSystem fs;
		string OperativeData(gData.m_DataDir + "Optimization/");
		if (fs.DirectoryExists(OperativeData))
			fs.RemoveAll(OperativeData);
		fs.MakeDirectory(OperativeData);

		m_SimulatorData.m_DataDir = OperativeData;

		DoLog("Data has been loaded");

		return true;
	}

	void CGasEnv::SetCurrentTask(CTrainingTask::TaskType Task)
	{
		gData.SetCurrentTask(Task);
	}

	EnvDescription CGasEnv::GetEnvDescription()
	{
		EnvDescription description;
		if (!GetModel()->IsLoaded())
		{
			DoLogForced("Failed to get env description because data was not loaded.");
			return description;
		}
		list<OptimizationParam*> optParams;
		GetOptimizationParams(optParams);

		description.m_bDiscrete = false;

#ifdef _FORCE_DISCRETE_ACTIONS
		description.m_bDiscrete = true;
#endif

		description.m_OpimizationParamsNumber = optParams.size();
		description.m_ObservationSpace = GetModel()->m_Ins.size() + GetModel()->m_Outs.size();
		
		if (EXPERIMENT > 1) {
			description.m_ObservationSpace += 2 * GetModel()->m_Shops.size(); // Pin and Pout for every shop
		}

		return description;
	}

	void CGasEnv::GetOptimizationParams(list<OptimizationParam*>& optParams)
	{
		for (auto pObject : GetModel()->m_GPAs) {
			BShopGPA *pGPA = dynamic_cast<BShopGPA*>(pObject);
			if (pGPA->m_State == 1)
				optParams.push_back(pGPA->GetParam(OParam::O_OB));
		}		
	}

	bool CGasEnv::Reset(string& info)
	{
		assert(gData.GetCurrentTask());
		if (!gData.GetCurrentTask())
		{
			info = "Task to be solved was not set.";
			return false;
		}

		gData.GetCurrentTask()->Reset();

		ClearErrorFiles(m_SimulatorData.m_DataDir);
		ClearResultFiles(m_SimulatorData.m_DataDir);
		ResetCalcEvents();
		
		
		// reload simulator
		// StopSimulations();
		// load / reload data
		// LoadData(gData.m_DataDir);

		LoadData(gData.m_DataDir);
		GetModel()->m_bSchemeChanged = true;

		SimulationStepResults Results;
		bool bResult = Step(&Results);
		GetModel()->m_bSchemeChanged = false;

		if (!bResult) {
			DoLogForced("Reloading simulator...");
			// reload simulator
			StopSimulations();
			// load / reload data
			LoadData(gData.m_DataDir);
			bResult = Step(&Results);
		}

		info = bResult 
			? (boost::format("Environment has been reset successfully. Current state info: %s") % gData.GetCurrentTask()->GetAdditionalInfo()).str()
			: "Environment reset failed. Probably, the initial dataset is not appropriate for system's modelling";
		DoLogForced(info);
		return bResult;
	}

	bool CGasEnv::Step(SimulationStepResults *pResults, bool bExportAll)
	{
		assert(pResults);

		ExportOperativeData(m_SimulatorData.m_DataDir, bExportAll);
		if (!DoSimulation(m_SimulatorData.m_lpEvents, m_SimulatorData.m_ProcessParams, m_SimulatorData.m_DataDir))
		{			
			DoLogForced("Internal error: DoSimulation failed");
			pResults->m_bDone = true;
			return false;
		}

		// Import simulation results
		bool bResult = GetModel()->ImportResults(m_SimulatorData.m_DataDir);
		gData.GetCurrentTask()->PostStep();
		if (bResult && !gData.GetCurrentTask()->IsDone())
		{
			pResults->m_Reward = gData.GetCurrentTask()->GetCurrentReward();
			pResults->m_Info = gData.GetCurrentTask()->GetAdditionalInfo();
		}
		else
		{
			pResults->m_bDone = true;
		}
		// save results of the task
		gData.GetCurrentTask()->StoreResults();

		DoLog(bResult ? "Simulation step succeded" : "Simulation step failed");
		return bResult;
	}


	void CGasEnv::ServeTrainedModel()
	{
		gData.SetCurrentTask(CTrainingTask::SERVING_MODEL);
		string Errors, Warnings;

		if (!GetModel()->LoadData(gData.m_DataDir, Errors, Warnings))
		{
			DoLogForced("Data path doesn't contain appropriate dataset.");
			DoLogForced("(" + gData.m_DataDir + ")");
			if (!Errors.empty())
				DoLogForced("Errors: " + Errors);
			if (!Warnings.empty())
				DoLogForced("Warnings: " + Warnings);
			return;
		}

		GetModel()->DynPrepare(gData.m_DataDir);
		string info;
		Reset(info);

		// Initialize predictor service client
		std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel("localhost:50052",
			grpc::InsecureChannelCredentials());
		std::unique_ptr<energyplatform::PredictorService::Stub> predictor_stub = energyplatform::PredictorService::NewStub(channel);
		

		int current_stratum = 0;
		while (true) {
			// print_stdout("Press any key to process timestep ...");
			// char t;
			// std::cin >> t;

			// temp: perturb P in in end process
			double p = dynamic_cast<BIn*>(GetModel()->m_Ins[0])->m_P;

			double range = 0.1; // perturbation range in ata
			double r = double(rand() % int(range*100) - rand() % int(range * 100)) / 100.;
			r = 0;

			dynamic_cast<BIn*>(GetModel()->m_Ins[0])->m_P = dynamic_cast<BIn*>(GetModel()->m_Ins[0])->m_P + r;
				
			p = dynamic_cast<BIn*>(GetModel()->m_Ins[0])->m_P;
			GetModel()->m_bSchemeChanged = true;

			// Get actions from Predictor service
			energyplatform::PredictRequest predict_request;
			SimulationServer::ServerMapper::CurrentObservationToProtobuf(predict_request.mutable_observation());

			energyplatform::PredictReponse predict_response;
			grpc::ClientContext context;
			grpc::Status status = predictor_stub->Predict(&context, predict_request, &predict_response);
			if (!status.ok()) {
				print_stdout(status.error_message());
			}
			else {
				for (auto eParam : predict_response.action().optimization_params()) {
					print_stdout("Got opt param: " + eParam.id() + " with value: " + itos(eParam.int_value()));

					RManagedParam *pParam = GetModel()->m_ControlParams[eParam.id()];
					if (!pParam) {
						print_stdout("   Param with id <" + eParam.id() + "> was not found");
						continue;
					}
					eParam >> (*pParam);
				}
			}
			
			// make one step
			SimulationStepResults Results;
			bool bResult = Step(&Results);
			if (bResult) {
				GetModel()->ExportResults(gData.m_DataDir);				
			}
			
			GetModel()->DynExport(current_stratum++);

			ResetEvent(m_hServingRunEvent);
			SetEvent(m_hServingConfirmEvent);

			HANDLE hArray[2];
			hArray[0] = m_hServingRunEvent;
			hArray[1] = m_hServingForceCloseEvent;

#ifndef _DEBUG
			DWORD dwCode = WaitForMultipleObjects(2, hArray, false, INFINITE);
#else
			DWORD dwCode = WAIT_OBJECT_0;
#endif

			switch (dwCode)
			{
			case WAIT_OBJECT_0:
				break;
			case WAIT_OBJECT_0 + 1:
				print_stdout("Serving stopped");
				StopSimulations();
				return;
				break;
			default:
				break;
			}
			
			print_stdout("New event has been processed");
		}
	}
}