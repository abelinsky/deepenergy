#include "pch.h"
#include "RManagedParam.h"
#include "BManagedObject.h"

namespace Objects {

	RManagedParam::RManagedParam(BManagedObject* pParent, double* pParam, OParam Code)
	{
		// m_uuId = to_string(boost::uuids::random_generator()());
		m_pParent = pParent;
		assert(m_pParent);
		m_Code = Code;
		m_pParam = pParam;
		m_OldValue = 0;
		PostCreate();
	}

	RManagedParam::~RManagedParam(void)
	{
	}

	void RManagedParam::GetParamBorders(double &min, double &max)
	{
		m_pParent->GetManagedParamBorders(this, min, max);
	}

	double RManagedParam::Get()
	{
		return m_pParent->GetParamValue(this);
	}

	void RManagedParam::Set(double Value)
	{
		m_OldValue = Get();
		m_pParent->SetParamValue(this, Value);
	}

	void RManagedParam::Off()
	{
		m_OldValue = Get();
	}

	void RManagedParam::On()
	{
		Set(m_OldValue);
	}

	double RManagedParam::GetDelta()
	{
		return m_pParent->GetParamDelta(this);
	}

	void RManagedParam::PostCreate()
	{
	}

	string RManagedParam::GetInfo()
	{
		return (boost::format("Parent object id: %1%, Param: %2%") % dynamic_cast<BObject*>(m_pParent)->m_ID % GetParamDescription(m_Code)).str();
	}

	string RManagedParam::GetUId()
	{
		return (boost::format("%1%_PARAM_%2%") % m_pParent->m_SID % m_Code).str();
	}

}