#include "pch.h"
#include "BShopObject.h"
#include "BShop.h"

namespace Objects {

BShopObject::BShopObject(void)
{
	m_pShop = NULL;
}

BShopObject::~BShopObject(void)
{
}

void BShopObject::PostAdd()
{
	assert(m_pShop);
}

void BShopObject::PostErased()
{
	assert(m_pShop);
}

}