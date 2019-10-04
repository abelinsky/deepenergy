#include "pch.h"
#include "TrainingTask.h"

namespace Tasks
{
	string CTrainingTask::GetTaskName(const TaskType &Type)
	{
		switch (Type)
		{
		case TaskType::MAX_THROUGHPUT:
			return "Расчет пропускной способности ГТС";
		case TaskType::OPTIMIZE:
			return "Оптимизация режима транспорта газа";
		}
		return "Неизвестный тип задачи.";
	}
}
