#pragma once
#include "TrainingTask.h"

namespace Tasks
{
	class CSimpleTask : public CTrainingTask
	{
	public:
		CSimpleTask();
		~CSimpleTask();

		double GetCurrentReward() override;
		
		string GetAdditionalInfo() override;

		void Reset() override;

		void StoreResults() override;

		bool IsDone() override;

		bool Is(TaskType type) override { return type == TaskType::SIMPLE; }

		void PostStep() override;

	protected:
		double CalcCurrentThroughput();

	private:
		// stored value of previuos throughput value
		double m_PrevThroughput;
		int m_StepsCount;
	};

}

