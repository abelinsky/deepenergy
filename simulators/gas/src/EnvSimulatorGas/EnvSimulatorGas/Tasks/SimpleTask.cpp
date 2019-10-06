#include "pch.h"
#include "SimpleTask.h"
#include "BOut.h"

namespace Tasks
{
	CSimpleTask::CSimpleTask()
	{
		Reset();
	}

	CSimpleTask::~CSimpleTask()
	{
	}

	double CSimpleTask::CalcCurrentThroughput()
	{
		double rQ = 0;
		for (BObject* pObject : GetModel()->m_Outs)
			rQ += abs(dynamic_cast<BOut*>(pObject)->m_rQ);
		return rQ;
	}

	void CSimpleTask::Reset()
	{
		m_PrevThroughput = 0;
		m_StepsCount = 0;
	}

	double CSimpleTask::GetCurrentReward()
	{
		if (m_PrevThroughput == 0.)
			return 0;

		double rq = CalcCurrentThroughput();
		double delta = rq - m_PrevThroughput;
		
		double multiplier = 1;
		double reward = delta >= 0
			? multiplier * exp(delta)
			: -exp(abs(delta));

		DoLogForced("   reward is " + ftos(reward) + " ______ prew q = " + ftos(m_PrevThroughput) + ", current q = " + ftos(rq));

		return reward;
	}

	string CSimpleTask::GetAdditionalInfo()
	{
		return (boost::format("Current throughput is %.2f") % CalcCurrentThroughput()).str();
	}

	void CSimpleTask::StoreResults()
	{
		m_PrevThroughput = CalcCurrentThroughput();
	}

	bool CSimpleTask::IsDone()
	{
		return m_PrevThroughput > CalcCurrentThroughput();
		// TODO: define the rule of finishing this task in config
		//double rq = CalcCurrentThroughput();
		//if (rq > 30)
		//{
		//	DoLogForced("Task is done, current throughput is " + ftos(rq));
		//	return true;
		//}
		return false;
	}

	void CSimpleTask::PostStep()
	{
		m_StepsCount += 1;
	}

}
