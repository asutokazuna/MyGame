/**
 * @file MissileCollision
 * @brief MissileCollision�N���X
 */
#include "MissileCollision.h"
#include "GameObject.h"

HRESULT MissileCollision::Init()
{
	m_isActive = false;

	Collision::Init();
	return S_OK;
}

void MissileCollision::Update()
{
	Collision::Update();
}

// EOF