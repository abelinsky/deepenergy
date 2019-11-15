#pragma once
#include <grpcpp/grpcpp.h>
#include "energyplatform/core/predictor_service.grpc.pb.h"

namespace Core 
{
	struct SimulationStepResults
	{
		// Observation m_NewObservation;
		double m_Reward;
		bool m_bDone;
		string m_Info;

		SimulationStepResults()
		{
			m_Reward = 0;
			m_bDone = false;
		}
	};

	struct EnvDescription
	{
		int m_OpimizationParamsNumber;
		int m_ObservationSpace;
		bool m_bDiscrete;
		
		EnvDescription()
		{
			m_OpimizationParamsNumber = 0;
			m_ObservationSpace = 0;
			m_bDiscrete = false;
		}
	};

	class CGasEnv
	{
	public:
		CGasEnv();
		~CGasEnv();

	protected:
		struct ThreadData
		{
			string m_InitialDir; // путь к каталогу с исходными данными для расчета
			string m_DataDir;    // путь к каталогу с оперативными данными расчетного модуля
			// CObjectsModel *m_pModel; // объектная модель
			HANDLE m_lpEvents[2]; // указатели на события
			string m_ProcessParams; // параметры запуска Calc.dll
		} m_SimulatorData;

		// Performs one calc event
		bool DoSimulation(HANDLE lpEvents[2], const string& ProcessParams, const string& DataDir);

		// Delete files with simulations errors
		void ClearErrorFiles(const string &DataDir);
		
		// Delete files with simulations results
		void ClearResultFiles(const string &DataDir);

		// Start simulations
		HANDLE StartSimulator(const string& processParams);

		void ExportOperativeData(const string& DataDir, bool bExportAll = false);

		void ExportOperativeShopData(const string& DataDir, bool bExportAll = false);

		void ExportShopData(const string& DataDir);

		// reset the events for Calc.exe
		void ResetCalcEvents();

	public:
		/* Model training */

		// Loads data
		bool LoadData(const string& FullPath);

		// Returns env description
		EnvDescription GetEnvDescription();

		// Loads data, resets simulations
		bool Reset(string& info);

		// Sets current task 
		void SetCurrentTask(CTrainingTask::TaskType);
		
		// Performs one simulation step
		bool Step(SimulationStepResults* pResults, bool bExportAll = true);
		
		// Stops simulations
		void StopSimulations();

		// Returns allowed agent's actions
		void GetOptimizationParams(list<OptimizationParam*>& optParams);
		


		/* Trained model serving */
		bool PrepareForModelServing();
		// Performs one ste on serving model
		void StepServingModel(std::unique_ptr<energyplatform::PredictorService::Stub> &predictor_service, int &current_stratum);

	public:
		HANDLE m_hCalcProcess;

		// Training mode interprocess sync events
		HANDLE m_hDynRunEvent_calc;
		HANDLE m_hDynConfirmEvent_calc;

		// Serving mode interprocess sync events
		HANDLE m_hServingRunEvent;
		HANDLE m_hServingConfirmEvent;
		HANDLE m_hServingForceCloseEvent;

	};

}