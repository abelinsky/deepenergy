#pragma once
#include "RManagedParam.h"

namespace Objects
{
	// ����� ����������� ��������
	class BManagedObject
	{
	public:
		BManagedObject(void);
		virtual ~BManagedObject(void);
		virtual string GetName() {return m_SID;}
		RManagedParam* GetParam(OParam);
		// ���������� ������� ������������� ������������ ���������
		virtual void GetManagedParamBorders(RManagedParam*, double &min, double &max) {}
		virtual void SetParamValue(RManagedParam*, double Value);
		virtual double GetParamValue(RManagedParam*);
		virtual void PostCalculate(bool bPostCalculateChilds = false){}

		virtual void Off(){}
		virtual void On(){}

		virtual double GetParamDelta(RManagedParam*) {return 0;}
		// ��������� ���������� ��������
		unordered_map <OParam, RManagedParam*> m_pParams;
		string m_SID;		// ��������� ������������� �������
	};
}
