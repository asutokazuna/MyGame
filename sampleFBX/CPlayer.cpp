/**
 * @file CPlayer
 * @brief プレイヤークラス
 * @date 2020/06/19
 */
#include "CPlayer.h"
#include "Object3D.h"
#include "collision.h"
#include "PlayerMove.h"
#include "PlayerCtrl.h"
#include "Rigidbody.h"
#include "Weapon.h"
#include "Geometry.h"
#include "PlayerShotDir.h"
#include "GameObject.h"
#include "PlayerState.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void CPlayer::Awake()
{
	transform->position.z = -500;
	tag = OBJ_TAG_PLAYER;

	AddComponent<PlayerMove>();
	//AddComponent<Rigidbody>();
	AddComponent<Object3D>()->SetModel(MODEL_PLAYER);
	m_col = AddComponent<Collision>();
	m_col->SetModelKind(MODEL_PLAYER);

	m_Weapon = new Weapon(20);
	m_Weapon->SetTag(OBJ_TAG_PLAYERMISSILE);
	SetChild(m_Weapon);

	m_ShotCol = new Cube();
	m_ShotCol->GetTransform().scale = (Vector3(150, 250, 1200));
	m_ShotCol->AddComponent<PlayerShotDir>();
	m_ShotCol->AddComponent<Collision>();
	SetChild(m_ShotCol);

	AddComponent<PlayerCtrl>();
	AddComponent<PlayerStateMachine>();
}

// EOF