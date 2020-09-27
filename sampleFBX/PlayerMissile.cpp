/**
 * @file PlayerMissile
 * @brief プレイヤーミサイルクラス
 */
#include "PlayerMissile.h"
#include "Missile.h"
#include "CCamera.h"
#include "Graphics.h"
#include "ModelData.h"
#include "Object3D.h"
#include "collision.h"
#include "MissileCollision.h"


HRESULT PlayerMissile::Init()
{
	{
		m_col = AddComponent<MissileCollision>();
		m_col->SetSize({ 20,20,20 })->SetPos(transform->position)
			->SetActive(false);
		m_col->SetTag(Collision::COL_MISSILE);
	}
	tag = Collision::COL_MISSILE;
	Missile::Init();
	m_col->SetTag(Collision::COL_MISSILE);
	return S_OK;
}

// EOF