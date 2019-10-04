#pragma once
#include "Node.h"

namespace Connections
{
	class CConnectionsMatrix
	{
	public:
		CConnectionsMatrix(void);
		~CConnectionsMatrix(void);
		void Clear();
		void AddNode(CNode*);
		CNode* GetNode(int NodeID);
		CNode* EraseNode(int NodeID);
		// �������� ������
		// unordered_map<int, int> *pMapChange - ��������� �� map: [ID �������]=[������ �������] (���� ��������� ��������)
		// ������ ������� ��� ���������� ��������, �.�. ��������� ������ ������� ���� (��������, ��������� ��
		// ������ ������� ������ ��������
		bool LoadData(istream&, string &Error, unordered_map<int, int> *pMapChange = NULL);
		void PrintExportData(ostream&);
		// ���������� ���� ����� ����� ������
		bool GetEdges(int NodeStart, int NodeEnd, list <int> &ResultList);
		// ������������ �������
		void Clone(CConnectionsMatrix &DestinationMatrix);
		// ������� �����
		void AddEdge(BObject*);
		// ����� �������� ������ ���� ��������
		void PostObjectsLoad();

		inline unordered_map <int, CNode*>& GetNodes() { return m_Nodes; }

	public:
		unordered_map <int, CNode*> m_Nodes;
		int m_EdgesCount;
		int m_nLineElements;
		int m_MaxID;
		int m_MaxNodeID;
	};
}