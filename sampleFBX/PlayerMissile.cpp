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


void PlayerMissile::Awake()
{
	tag = OBJ_TAG_PLAYERMISSILE;
	Missile::Awake();

	{
		m_col = AddComponent<Collision>();
		m_col->SetSize({ 20,20,20 })->SetPos(transform->position)
			->SetActive(false);
		m_col->SetModelKind(MODEL_MISSILE);
	}
}

// EOF