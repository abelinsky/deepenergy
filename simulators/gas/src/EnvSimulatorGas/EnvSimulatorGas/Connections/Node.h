#pragma once

namespace Objects
{
	class BObject;
}

namespace Connections
{
	
	class CNode
	{
	public:
		CNode(void);
		CNode(int ID);
		~CNode(void);
		// �������� �����
		void AddEdgeIn(BObject*);
		void AddEdgeIn(int ID);
		// ��������� �����
		void AddEdgeOut(BObject*);
		void AddEdgeOut(int ID);
		// �����������
		void Attach(CNode*);
		void Clear();
		// ���������� � ������ ���� ����� � ����
		void CollectEdges(list<int>&);
		// ������������ ����� ��������� �����������
		void ExportInitData(ostream&);
		// ������������ �������� Pmin, Pmax
		void PostObjectsLoad();
		// �������� ����� �� ����
		bool EraseEdge(int ID);
	public:
		int m_ID;
		vector <int> m_InEdges;		// �����, �������� � ����
		vector <int> m_OutEdges;	// �����, ��������� �� ����

		vector <int> m_Ins;			// ������� � ����
		vector <int> m_Outs;		// ������ �� ����

		double m_Pmin;
		double m_Pmax;
		double m_rP;				// ��������� �������� � ���� [���]
		double m_rT;				// ��������� ����������� � ���� [0�]
	};
}