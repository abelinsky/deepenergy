#pragma once
#include "BManagedObject.h"

namespace Objects
{
	class BShopGPA;
	class BShopGPAGroup;
	class BShopBypass;
	class BShopObject;
	class RShopsGroup;
	// КЦ
	class BShop : public BObject
	{
	public:
		BShop(void);
		virtual ~BShop(void);
		virtual int GetMatrixID();
		virtual void LoadData(istream&);
		virtual bool CheckLoadedData(string& Error);
		void ClearShop();
		bool AddGroup(BShopGPAGroup*, bool bResults = false);
		BShopGPAGroup* GetGroup(int GroupID, bool bResults = false);
		void AddChild(BShopObject*);
		virtual void PostAdd();
		virtual void PostErased();
		virtual bool CanExport();
		void PrintExportLosts(ostream& lost_ad, ostream& lost);
		virtual void PrintExportData(ostream&);
		virtual void ClearResults();
		virtual void ImportResults(istream&);
		virtual void ExportResults(ostream&);
		void InputShopResults(istream&);
		virtual void PostCalculate(bool bPostCalculateChilds = false);
		void ExportShopResults(ostream&);
		virtual bool PrintInitData(ostream&, bool bOut=true);
		virtual string GetName();
		virtual bool GetPminMax(double& Pmin, double& Pmax);
		virtual bool IsFlowMode();
		void SetFlowMode(bool bFlowMode = true);
		virtual bool IsShop() { return true; }
		virtual void GetManagedParamBorders(RManagedParam*, double &min, double &max);
		// Возвращает диапазон поправок на обороты ГПА КЦ с учетом контроля мин. и макс. оборотов ГПА
		// и значение поправки на обороты, чувствительной к частоте вращения
		void CalcKnRange(double &kmin, double &kmax);
		virtual void ResultsToObject(); // экспорт результатов расчетов в параметры КЦ и объектов КЦ
		virtual void CheckResults();
		void ImportGroupResults();
		virtual void InitForExport();
		virtual void SetCalculated(bool bCalculated = true);
		virtual void SummA(double *pA, OptEnums::TypeA type);
		
	public:
		static unordered_map <int, int> sLoadingMap; // допустимое количество "Всего ГПА в КЦ - количество резервных"

		vector <BShopGPA*> m_pAllGPAs;
		unordered_map <int, BShopGPA*> m_GPAs;
		vector <BShopBypass*> m_Bypasses;
		unordered_map <int, BShopGPAGroup*> m_WorkingGroups;
		BShopGPAGroup* m_pGroupDisabled;
		RShopsGroup* m_pGroup; // Группа параллельных КЦ, включая данный

		string m_Name;
		bool m_bWShop;			// Цех, состоящий только из электроприводных ГПА
		string m_KSName;		// Название КС(char)
		int m_ThreadNumber;		// Номер нитки МГ
		int m_ShopNumber;		// Номер цеха 
		double m_kE;			// Коэф. адаптации КЦ по степени сжатия
		double m_kK;			// Коэф. адаптации КЦ по кпд
		double m_kn;			// Коэф. адаптации КЦ по оборотам
		double m_Qcost;			// Цена руб/тыс. м3    (топливный газ)
		double m_Wcost;			// Цена руб/(кВт час)  (электроэнергия)
		int m_RDValvesCount;	// Количество кранов байпасирования, также является признаком, что режим байпасирования разрешен
		double m_dE;			// Степень сжатия КЦ, для потокового режима 
		double m_dP;			// Дельта Р, для потокового режима 
		double m_dT;			// Дельта Т, для потокового режима 
		double m_dQ;			// Дельта Q, для потокового режима 
		int m_LostKind;			// Признак расчета потокового режима КЦ: 1 - по dP, 2 - по степени сжатия
		bool m_bFlowMode;		// Признак, расчитывается ли КЦ как потоковый объект
		
		double m_Tair;			// Температура воздуха [0С]
		double m_Pair;			// Давление воздуха [ата]
		double m_Pinmin;		// Минимально допустимое давление газа [ата]
		double m_Poutmax;		// Максимально допустимое давление газа [ата]
		double m_Toutmax;		// Максимально допустимая температура газа на выходе КЦ [0C]
		double m_dPin;			// Потери давления на входе КЦ [ ата]
		double m_dPout;			// Потери давления на выходе КЦ  [ата] 
		int m_nShopGPAs;		// Общее количество ГПА в КЦ 
		int m_nWGroupsCount;	// Количество работающих групп
		int m_nShopGPAReserve;	// Кол-во ГПА в резерве 
		int m_AVOID;			// Идентификатор (шифр) типа АВО 
		int m_nAVOCount;		// Количество АВО  
		int m_nVentAVOCount;	// Кол-во работающих вентиляторов
		double m_AVOT_dt;		// Уставка температуры газа на выходе АВО [0C]  (dT когда схема и НСИ по АВО отсутствует)
		double m_Poutmin;		// Минимально допустимое давление газа на выходе КЦ   задавать 0.0
		double m_Qmax;			// Максимальный расход ограничение [млн.м3/сут] задавать 0.0
		double m_Qtg;			// Расход газа на технологич. нужды по КЦ [млн.м3/сут]
		double m_Pset;			// Уставка по давлению нагнетания [ата] ****
		double m_Emax;			// Максимально-допустимая степень сжатия ****
		double m_Emin;			// Минимально-допустимая степень сжатия ****
		int m_CalcType;			// Маркер режима расчета (0 – фиксированы обороты и схема,
								// 1 -  фиксирована схема опред. обороты,
								// 2 – определяются и схема и обороты,
								// 3 – расчет по упрощенной модели)
								// 4 – определение схем и оборотов без отключения КЦ

		// Результаты расчета

		double m_rCO2;										// % СО2
		double m_rN2;										// % N2

		unordered_map <int, BShopGPAGroup*> m_rWorkingGroups;	// Группы
		double m_A;											// эквивалентная товаротранспортная работа
		double m_B;											// Расход топливно-энергетических ресурсов
		double m_rsE;										// Степень сжатия
		double m_rsTng;										// Температура нагнетания [0С]
		double m_rsQtg;										// Расход топливного газа [млн.м3/сут]		
		double m_rsQon;										// Расход газа на собственные нужды [млн.м3/сут]
		double m_rsW;										// Расход электроэнергии [кВт/час]
		double m_rsN;										// Мощность, потреб. нагнетат.  [кВт]
		double m_rsNres;									// Резерв мощности  [кВт]
		double m_rsQb;										// Расход байпасир. [млн.м3/сут]
		int m_rsAVOcount;									// Кол-во раб.АВО
		int m_rsAVOVent;									// Кол-во вент в 1 АВО
		double m_rsEff;										// Удельный показатель эффективности расхода газа на СТН КЦ на единицу работы, [м3/млн.м3*км]
		double m_rsL;										// Политропная работа сжатия КЦ [кВт*ч]
		double m_rsWAVO;									// Затраты э/э в АВО [кВт*ч]

		double m_rsQtgCost;									// Стоимость топливного газа [тыс.руб.]
		double m_rsWCost;									// Стоимость электроэнергии, расходуемой ЭГПА [тыс.руб.]
		double m_rsWAVOCost;								// Стоимость электроэнергии, расходуемой АВО [тыс.руб.]
	};
}



