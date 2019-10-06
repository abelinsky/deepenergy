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
			string m_InitialDir; // ���� � �������� � ��������� ������� ��� �������
			string m_DataDir;    // ���� � �������� � ������������ ������� ���������� ������
			// CObjectsModel *m_pModel; // ��������� ������
			HANDLE m_lpEvents[2]; // ��������� �� �������
			string m_ProcessParams; // ��������� ������� Calc.dll
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
		void ResetEvents();

		// loads data and calculates env description params
		bool RecalculateEnvDescriptionParams();

	public:

		// Loads data
		bool LoadData(const string& FullPath);

		// Returns env description
		const EnvDescription& GetEnvDescription();

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
		

	public:
		HANDLE m_hCalcProcess;
		HANDLE m_hDynRunEvent;
		HANDLE m_hDynConfirmEvent;
		std::thread* m_pCalcThread;

	protected:
		EnvDescription m_EnvDescription;
	};

}