/**
 * @file PlayerCollision
 * @brief PlayerCollision�N���X
 */
#pragma once
#include "collision.h"

class PlayerCollision :public Collision
{
public:
	virtual void Check(Collision* othor);
	HRESULT Init();
	void Update();
	void Draw();
};

// EOF