/**
 * @file TowerCollision
 * @brief TowerCollisionƒNƒ‰ƒX
 */
#pragma once
#include "collision.h"

class GameObject;

class TowerCollision :public Collision
{
public:
	HRESULT Init();
	virtual void OnCollisionEnter(GameObject* othor);
	void UpdatePos();
};

// EOF