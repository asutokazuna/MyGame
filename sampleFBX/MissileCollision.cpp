/**
 * @file MissileCollision
 * @brief MissileCollisionƒNƒ‰ƒX
 */
#include "MissileCollision.h"
#include "GameObject.h"

HRESULT MissileCollision::Init()
{
	m_tag = COL_MISSILE;
	size = 20.0f;
	pos = m_Parent->GetTransform().position;
	m_isActive = false;

	Collision::Init();
	return S_OK;
}

void MissileCollision::Update()
{
	pos = m_Parent->GetTransform().position;
	Collision::Update();
}

// EOF