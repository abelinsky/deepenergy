#pragma once

namespace Objects
{
	class BValve : public BObject
	{
	public:
		BValve(void);
		virtual ~BValve(void);
		virtual int GetMatrixID();
		virtual void PostAdd();
		virtual void PostErased();
		virtual void ImportResults(istream&);
		virtual void ExportResults(ostream&);
		virtual void ClearResults();

	public:
		// ���������� �������
		double m_rDirection;	// ������� ����.������ 1-�� ���./0
	};
}