#include "pch.h"
#include "BManagedObject.h"

namespace Objects {

BManagedObject::BManagedObject(void)
{
}

BManagedObject::~BManagedObject(void)
{
	for (unordered_map <OParam, RManagedParam*>::iterator i = m_pParams.begin(); i != m_pParams.end(); i++)
		delete i->second;
	m_pParams.clear();
}

void BManagedObject::SetParamValue(RManagedParam *pParam, double Value)
{
	(*pParam->m_pParam) = Value;
}

double BManagedObject::GetParamValue(RManagedParam *pParam)
{
	return (*pParam->m_pParam);
}

RManagedParam* BManagedObject::GetParam(OParam Code)
{
	if (m_pParams.find(Code) != m_pParams.end())
		return m_pParams[Code];
	return NULL;
}

}