/**
 * @file CoreEnemy.h
 * @brief 敵チームのコアクラス
 */
#include "CoreEnemy.h"
#include "CoreCollision.h"

#define CORE_POS_Z (600)

HRESULT CoreEnemy::Init()
{
	Core::Init();

	transform->position.z = CORE_POS_Z;
	m_Collision->SetTag(Collision::COL_CORE_ENEMY);
	m_Collision->SetTarget(Collision::COL_MISSILE);

	return E_NOTIMPL;
}
