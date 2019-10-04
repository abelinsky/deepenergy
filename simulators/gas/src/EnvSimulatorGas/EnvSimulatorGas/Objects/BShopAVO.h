#pragma once

#include "BShopObject.h"

namespace Objects
{
	class BShopAVO : public BShopObject
	{
	public:
		BShopAVO(void);
		virtual ~BShopAVO(void);
		virtual int GetMatrixID();
	};
}