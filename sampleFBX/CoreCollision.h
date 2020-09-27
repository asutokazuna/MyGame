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
	HRESULT Init();
	void Check(Collision* tag);
	void SetTarget(int colTag);
};

// EOF