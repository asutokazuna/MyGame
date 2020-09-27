/**
 * @file CorePlayer.h
 * @brief 味方チームのコアクラス
 */
#include "CorePlayer.h"
#include "CoreCollision.h"

#define CORE_POS_Z (-600)

HRESULT CorePlayer::Init()
{
	Core::Init();

	transform->position.z = CORE_POS_Z;
	m_Collision->SetTag(Collision::COL_CORE_PLAYER);
	m_Collision->SetTarget(Collision::COL_MISSILE_ENEMY);

	return E_NOTIMPL;
}

// EOF