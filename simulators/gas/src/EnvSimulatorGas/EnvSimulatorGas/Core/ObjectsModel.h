#pragma once

#include "pch.h"
#include "BObject.h"
#include "BGTS.h"
#include "RShopsGroup.h"
#include "BNSIGPA.h"
#include "BNSIAVO.h"
#include "ConnectionsMatrix.h"
#include "DMapFile.h"

namespace Core
{
	struct Disbalance
	{
		Disbalance(void)
		{
			Clear();
		}
		void Clear()
		{
			m_Node = 0;
			m_Q = 0;
			m_P = 0;
		}
		void operator = (Disbalance &Source)
		{
			m_Node = Source.m_Node;
			m_Q = Source.m_Q;
			m_P = Source.m_P;
		}
		int m_Node;
		double m_Q;
		double m_P;
	};

	class CObjectsModel
	{
	public:
		CObjectsModel(void);
		~CObjectsModel(void);
		void Clear();
		bool LoadData(const string& DataDir, string& Errors, string &Warnings);
		void ExportData(const string& DataDir);
		
		// Prepares to IO in real time
		bool DynPrepare(const string& DataDir);
		
		// Export current data to specified stratum of shared memory files
		bool DynExport(int stratum);

		bool ImportResults(const string& ResultsDir);
		void ExportResults(const string& Dir);
		void AddObject(BObject*);
		void EraseObject(BObject*);
		BObject* GetObject(int ID);
		bool AddNSIGPA(BNSIGPA*, string& Error);
		BNSIGPA* GetNSIGPA(int ID);
		bool AddNSIAVO(BNSIAVO*, string& Error);
		BNSIAVO* GetNSIAVO(int ID);
		void InputShopResults(const string& FilePath, bool bResultsToObject = false);
		void InputEfficiencyResults(const string &ResultShopEf);
		int CountGroupLosts();
		void SetFlowMode(bool bFlowModel = true);
		bool IsLoaded() { return !m_Objects.empty(); }
		inline bool IsFlowMode() { return m_bFlowMode; }
		inline Connections::CConnectionsMatrix& GetConnectionsMatrix() { return m_Connections; }
		inline const list <BObject*>& GetObjectsList() { return m_ObjectsList; }
		inline const vector <BObject*>& GetPipes() { return m_Pipes; }
		
		// Defines allowable actions (managable/control params)
		void DefineControlParams();

	protected:
		void ExportResults(ostream&, vector <BObject*>&);

	public:
		Connections::CConnectionsMatrix m_Connections;
		list <BObject*> m_ObjectsList;
		unordered_map <int, BObject*> m_Objects;
		unordered_map <int, BNSIGPA*> m_NSIGPA;
		unordered_map <int, BNSIAVO*> m_NSIAVO;
		unordered_map <string, RManagedParam*> m_ControlParams;  // manageable params with unique identifiers which are set in a consistent way 
		BGTS* m_pGTS;
		vector <BObject*> m_Ins;
		vector <BObject*> m_Outs;
		vector <BObject*> m_Pipes;
		vector <BObject*> m_Losts;
		vector <BObject*> m_GPAs;
		vector <BObject*> m_RDValves;
		vector <BObject*> m_Shops;
		vector <BObject*> m_Valves;
		
		// группы параллельных КЦ
		vector <RShopsGroup*> m_ParallelShops;

		DMapFile m_InOutMap;

		int m_nMaxNSIID;

		bool m_bSchemeChanged; // признак, что изменилась схема (изменилось представление КЦ - схемами или степенью сжатия)
		list <Disbalance> m_rDisbalances;
		double m_rSummDisbalance;
		int m_rEdgesCount; // количество рассчитанных ребер
		bool m_bFlowMode;

		// Результаты расчета (статистика)
		double m_rQtg;										// Расход топливного газа [млн.м3/сут]
		double m_rW;										// Расход электроэнергии ЭГПА [кВт/час]
		double m_rN;										// Мощность, потребляемая ЦБН, кВт
		double m_rsL;										// Политропная работа сжатия КЦ [кВт*ч]
		double m_rsWAVO;									// Затраты э/э в АВО [кВт*ч]

		double m_rsQtgCost;									// Стоимость топливного газа [тыс.руб.]
		double m_rsWCost;									// Стоимость электроэнергии, расходуемой ЭГПА [тыс.руб.]
		double m_rsWAVOCost;								// Стоимость электроэнергии, расходуемой АВО [тыс.руб.]

		double m_rTinDelta;									// Средневзвешенное отклонение температур газа на входе компрессорных цехов от температур грунта 

		double m_A_ttr;										// ТТР ГТС, [млн.м3/км]
		double m_A_ettr;									// ЭТТР ГТС, [млн.м3/км]
		double m_A_ottr;									// ОТТР ГТС, [млн.м3/км]

		double m_RestrictionsP;								// сумма нарушений ограничений по давлениям газа в узлах расчетного графа
	};
}