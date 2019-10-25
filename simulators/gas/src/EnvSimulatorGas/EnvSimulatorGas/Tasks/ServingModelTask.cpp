#include "pch.h"
#include "ServingModelTask.h"
#include "BOut.h"

namespace Tasks
{
	CServingModelTask::CServingModelTask()
	{
		Reset();
	}

	CServingModelTask::~CServingModelTask()
	{
	}


	void CServingModelTask::Reset()
	{
	}

	double CServingModelTask::GetCurrentReward()
	{
		return 0;
	}

	string CServingModelTask::GetAdditionalInfo()
	{
		return "";
	}

	void CServingModelTask::StoreResults()
	{
	}

	bool CServingModelTask::IsDone()
	{
		return false;
	}

	void CServingModelTask::PostStep()
	{
	}

}
