#include "pch.h"
#include "TrainingTask.h"

namespace Tasks
{
	string CTrainingTask::GetTaskName(const TaskType &Type)
	{
		switch (Type)
		{
		case TaskType::MAX_THROUGHPUT:
			return "������ ���������� ����������� ���";
		case TaskType::OPTIMIZE:
			return "����������� ������ ���������� ����";
		}
		return "����������� ��� ������.";
	}
}
