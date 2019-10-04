#pragma once

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
		int m_ActionsNumber;
		int m_ObservationSpace;
		
		EnvDescription()
		{
			m_ActionsNumber = 0;
			m_ObservationSpace = 0;
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

		bool LoadData(const string& FullPath);

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
		void ResetEvents();

		// loads data and calculates env description params
		void RecalculateEnvDescriptionParams();

	public:

		// Sets data location
		void SetDataLocation(const string& FullPath);

		// Returns env description
		const EnvDescription& GetEnvDescription(bool bReloadAndCalculate = true);

		// Loads data, resets simulations
		bool Reset(string& info);

		// Sets current task 
		void SetCurrentTask(CTrainingTask::TaskType);
		
		// Performs one simulation step
		bool Step(SimulationStepResults* pResults, bool bExportAll = true);
		
		// Stops simulations
		void StopSimulations();

		// Returns allowed agent's actions
		void GetAllowedActions(list<ObjectAction*>& allowedActions);
		

	public:
		HANDLE m_hCalcProcess;
		HANDLE m_hDynRunEvent;
		HANDLE m_hDynConfirmEvent;
		std::thread* m_pCalcThread;

	protected:
		EnvDescription m_EnvDescription;
	};

}