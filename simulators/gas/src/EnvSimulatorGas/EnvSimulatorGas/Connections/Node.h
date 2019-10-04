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
		// входящее ребро
		void AddEdgeIn(BObject*);
		void AddEdgeIn(int ID);
		// выходящее ребро
		void AddEdgeOut(BObject*);
		void AddEdgeOut(int ID);
		// Копирование
		void Attach(CNode*);
		void Clear();
		// Добавление в вектор всех ребер в узле
		void CollectEdges(list<int>&);
		// Формирование файла начальных приближений
		void ExportInitData(ostream&);
		// Формирование значений Pmin, Pmax
		void PostObjectsLoad();
		// Удаление ребра из узла
		bool EraseEdge(int ID);
	public:
		int m_ID;
		vector <int> m_InEdges;		// ребра, входящие в узел
		vector <int> m_OutEdges;	// ребра, исходящие из узла

		vector <int> m_Ins;			// притоки в узел
		vector <int> m_Outs;		// отборы из узла

		double m_Pmin;
		double m_Pmax;
		double m_rP;				// Расчетное давление в узле [ата]
		double m_rT;				// Расчетная температура в узле [0С]
	};
}