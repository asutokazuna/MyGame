/**
 * @file CoreCollision
 * @brief CoreCollisionƒNƒ‰ƒX
 */
#pragma once
#include "collision.h"

class CoreCollision :public Collision
{
protected:
	int m_ColTarget;
public:
	CoreCollision();
	void Check(Collision* tag);
};

// EOF