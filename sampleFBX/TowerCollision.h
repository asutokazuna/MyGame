/**
 * @file TowerCollision
 * @brief TowerCollisionƒNƒ‰ƒX
 */
#pragma once
#include "collision.h"

class TowerCollision :public Collision
{
public:
	HRESULT Init();
	virtual void Check(Collision* othor);
	void UpdatePos();
};

// EOF