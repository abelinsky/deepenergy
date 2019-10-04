#pragma once

namespace Objects
{
	class BShopGPA;
	class BShopGPAGroup
	{
	public:
		BShopGPAGroup(void);
		virtual ~BShopGPAGroup(void);
		inline void AddShopGPA(BShopGPA *pShopGPA) {m_pGPAs.push_back(pShopGPA);}

	public:
		vector <BShopGPA*> m_pGPAs;
		int m_ID;			// номер группы в КЦ
		int m_nStages;		// Количество ступеней в группе
	};
}