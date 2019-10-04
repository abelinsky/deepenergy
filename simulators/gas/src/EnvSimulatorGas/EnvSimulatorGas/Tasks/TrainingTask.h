#pragma once

namespace Tasks
{
	class CTrainingTask
		// AI Training task
	{
	public:
		enum TaskType
		{
			UNDEFINED = 0,
			SIMPLE = 1,								// Fixed simple training example (gas pipeline with one compression shop, equiped with one ShopGPA)
			FEED_FORWARD = 105,						// ������ ������ ���������� ������
			AVAILABLE_TECHNOLOGICAL_MODE = 106,		// ����� ����������� ���������������� ������
			MAX_THROUGHPUT = 107,					// ������ ������������ ���������� �����������
			OPTIMIZE = 108							// ���������� ����������������� ������ ���������� ����
		};

	public:
		virtual ~CTrainingTask() {}

		static string GetTaskName(const TaskType &Type);

		// Returns current reward 
		virtual double GetCurrentReward() = 0;

		// Gets additional info about current episode
		virtual string GetAdditionalInfo() = 0;

		// Resets the task
		virtual void Reset() = 0;

		// Stores the results of current episode
		virtual void StoreResults() = 0;

		// Returns the state of the task
		virtual bool IsDone() { return false; }

		virtual bool Is(TaskType type) = 0;

		// Called after env step
		virtual void PostStep() {}

	};
}