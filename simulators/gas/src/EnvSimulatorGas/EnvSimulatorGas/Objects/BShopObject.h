#pragma once

namespace Objects
{
	class BShop;
	class BShopObject : public BObject
	{
	public:
		BShopObject(void);
		virtual ~BShopObject(void);
		virtual void PostAdd();
		virtual void PostErased();

	public:
		BShop* m_pShop;
	};
}