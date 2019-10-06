#include "pch.h"
#include "MaxThroughputTask.h"
#include "BOut.h"

namespace Tasks
{
	CMaxThroughputTask::CMaxThroughputTask()
	{
		Reset();
	}

	CMaxThroughputTask::~CMaxThroughputTask()
	{
	}

	double CMaxThroughputTask::CalcCurrentThroughput()
	{
		double rQ = 0;
		for (BObject* pObject : GetModel()->m_Outs)
			rQ += abs(dynamic_cast<BOut*>(pObject)->m_rQ);
		return rQ;
	}

	void CMaxThroughputTask::Reset()
	{
		m_PrevThroughput = 0;
	}

	double CMaxThroughputTask::GetCurrentReward()
	{
		return 0;

		//if (m_PrevThroughput == 0.)
		//	return 0;

		//double rq = CalcCurrentThroughput();
		//double delta = rq - m_PrevThroughput;

		//double eps = 0.1;
		//return delta > eps
		//	? sgn(delta) * exp(abs(delta))
		//	: 0;

		//return delta > 0
		//	? exp(delta)
		//	: -exp(abs(delta));

		//return (delta > 0.1) // we increased throughput over than 0.1 % ?
		//	? exp(delta)
		//	: 0;
	}

	string CMaxThroughputTask::GetAdditionalInfo()
	{
		return (boost::format("Current throughput is %.2f") % CalcCurrentThroughput()).str();
	}

	void CMaxThroughputTask::StoreResults()
	{
		m_PrevThroughput = CalcCurrentThroughput();
	}

}
