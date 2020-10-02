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
	}
	tag = OBJ_TAG_PLAYERMISSILE;
	Missile::Init();
	m_col->SetActive(false);
	m_col->SetModelKind(MODEL_MISSILE);
	return S_OK;
}

// EOF