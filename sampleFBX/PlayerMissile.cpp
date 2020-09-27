/**
 * @file PlayerMissile
 * @brief �v���C���[�~�T�C���N���X
 */
#include "PlayerMissile.h"
#include "Missile.h"
#include "CCamera.h"
#include "Graphics.h"
#include "ModelData.h"
#include "Object3D.h"
#include "collision.h"
#include "MissileCollision.h"

 //*****************************************************************************
 // �}�N����`
 //*****************************************************************************
#define SPEED			(15.0f)

HRESULT PlayerMissile::Init()
{
	m_col = AddComponent<MissileCollision>();
	Missile::Init();
	m_col->SetTag(Collision::COL_MISSILE);
	return S_OK;
}

// EOF