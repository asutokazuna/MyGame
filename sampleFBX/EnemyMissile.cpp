/**
 * @file EnemyMissile
 * @brief 敵ミサイル
 */
#include "EnemyMissile.h"
#include "collision.h"

HRESULT EnemyMissile::Init()
{
	m_col = AddComponent<Collision>();
	Missile::Init();
	tag = OBJ_TAG_ENEMYMISSILE;
	//m_col->SetTag(Collision::COL_MISSILE_ENEMY);
	m_col->SetActive(false);
	return S_OK;
}

// EOF