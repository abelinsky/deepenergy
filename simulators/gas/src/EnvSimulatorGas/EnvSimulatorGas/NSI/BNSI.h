#pragma once

namespace NSI
{
	class BNSI
	{
	public:
		BNSI(void);
		virtual ~BNSI(void);
		virtual void LoadData(istream&){}
		virtual bool CheckLoadedData(string& Error);
		virtual void PrintExportData(ostream&){}
	public:
		int m_ID;
	};
}