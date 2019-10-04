#pragma once

namespace Objects
{
	class BLost : public BObject
	{
	public:
		BLost(void);
		virtual ~BLost(void);
		virtual void LoadData(istream&);
		virtual int GetMatrixID();
		virtual void PostAdd();
		virtual void PostErased();
		virtual void PrintExportData(ostream&);

	public:
		double m_dP;	// Потери давления [ата]
		double m_dT;	// Потери температуры [град C]
		double m_dQ;	// Потери  расхода [млн.м3/сут]
	};
}