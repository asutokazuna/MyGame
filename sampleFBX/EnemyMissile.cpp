/**
 * @file EnemyMissile
 * @brief 敵ミサイル
 */
#include "EnemyMissile.h"
#include "MissileCollision.h"
#include "collision.h"

HRESULT EnemyMissile::Init()
{
	m_col = AddComponent<MissileCollision>();
	Missile::Init();
	m_col->SetTag(Collision::COL_MISSILE_ENEMY);
	m_col->SetActive(false);
	return S_OK;
}

// EOF