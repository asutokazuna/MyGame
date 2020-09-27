#include "EnemyMissile.h"
#include "MissileCollision.h"
#include "collision.h"

EnemyMissile::EnemyMissile()
{
}

EnemyMissile::~EnemyMissile()
{
}

HRESULT EnemyMissile::Init()
{
	m_col = AddComponent<MissileCollision>();
	Missile::Init();
	m_col->SetTag(Collision::COL_MISSILE_ENEMY);
	return S_OK;
}

// EOF