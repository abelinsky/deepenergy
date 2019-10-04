#pragma once
#include "TrainingTask.h"

namespace Tasks
{
	class CMaxThroughputTask : public CTrainingTask
	{
	public:
		CMaxThroughputTask();
		~CMaxThroughputTask();

		double GetCurrentReward() override;
		
		string GetAdditionalInfo() override;

		void Reset() override;

		void StoreResults() override;

		bool Is(TaskType type) override { return type == TaskType::MAX_THROUGHPUT; }

	protected:
		double CalcCurrentThroughput();

	private:
		// stored value of previuos throughput value
		double m_PrevThroughput;
	};

}

