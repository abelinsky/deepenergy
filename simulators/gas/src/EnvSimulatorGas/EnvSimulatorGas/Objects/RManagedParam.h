#pragma once


namespace Objects
{
	class BManagedObject;
	// ����������� ����������
	enum OParam
	{
		O_OB = 1,    // ������� ���
		O_SCHOB = 2, // ����� ������ ���
		O_ORD = 3,   // ������� �������� ������ ��
		O_E = 4,     // ������� ������ ���, �� � �.�.
		O_T = 5      // ����������� ������ �� (����� ��)
	};

	inline string GetParamDescription(OParam param) {
		switch (param)
		{
		case O_E:
			return "Compression ratio";
		case O_T:
			return "Temperature";
		default:
			return "Not defined";
		}
	}

	// ����� ������������ ���������, ���������� - ����������� (double)
	class RManagedParam
	{
	public:
		RManagedParam(BManagedObject* pParent, double* pParam, OParam Code);
		virtual ~RManagedParam();
		// ���������� ������� �������������
		void GetParamBorders(double &min, double &max);
		double Get();
		string GetUId();
		string GetInfo();
		void Set(double Value);
		//void Rollback();
		void Off();
		void On();
		double GetDelta(); // ��� ��� ������� �����������
		void PostCreate();
		bool IsDiscrete();

	public:
		// string m_uuId; // unique identifier

		BManagedObject* m_pParent;
		double* m_pParam;
		OParam m_Code;
		double m_OldValue;
	};

	typedef Objects::RManagedParam OptimizationParam;
}