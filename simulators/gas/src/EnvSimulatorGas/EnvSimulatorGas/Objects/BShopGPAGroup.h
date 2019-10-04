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
		int m_ID;			// ����� ������ � ��
		int m_nStages;		// ���������� �������� � ������
	};
}