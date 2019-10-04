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
		// Загрузка данных
		// unordered_map<int, int> *pMapChange - указатель на map: [ID объекта]=[Индекс матрицы] (если требуется заменять)
		// индекс матрицы для конкретных объектов, т.е. создавать объект другого типа (например, создавать КЦ
		// вместо объекта потерь давления
		bool LoadData(istream&, string &Error, unordered_map<int, int> *pMapChange = NULL);
		void PrintExportData(ostream&);
		// Возвращает дуги между двумя узлами
		bool GetEdges(int NodeStart, int NodeEnd, list <int> &ResultList);
		// клонирование матрицы
		void Clone(CConnectionsMatrix &DestinationMatrix);
		// Вставка ребра
		void AddEdge(BObject*);
		// после загрузки данных всех объектов
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