#pragma once
#include "TrainingTask.h"

namespace Tasks
{
	class CServingModelTask : public CTrainingTask
	{
	public:
		CServingModelTask();
		~CServingModelTask();

		double GetCurrentReward() override;
		
		string GetAdditionalInfo() override;

		void Reset() override;

		void StoreResults() override;

		bool IsDone() override;

		bool Is(TaskType type) override { return type == TaskType::SERVING_MODEL; }

		void PostStep() override;

	};

}

