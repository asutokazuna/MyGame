/**
 * @file MissileCollision
 * @brief MissileCollision�N���X
 */
#pragma once
#include "collision.h"

class MissileCollision :public Collision
{
public:
	HRESULT Init();
	void Update();
};

