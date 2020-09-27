/**
 * @file MissileCollision
 * @brief MissileCollisionƒNƒ‰ƒX
 */
#pragma once
#include "collision.h"

class MissileCollision :public Collision
{
public:
	HRESULT Init();
	void Update();
};

