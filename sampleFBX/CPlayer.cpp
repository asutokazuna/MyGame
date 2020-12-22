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
#include "Lockon.h"
#include "WeaponBulletCount.h"
#include "DigitNumber.h"

#define DIGIT (2)

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

	// 武器
	m_Weapon = new Weapon(20);
	m_Weapon->SetTag(OBJ_TAG_PLAYERMISSILE);
	SetChild(m_Weapon);

	AddComponent<PlayerShotDir>();
	// ロックオン
	GameObject* obj = new Lockon();
	SetChild(obj);

	for (int i = 0; i < DIGIT; i++)
	{
		DigitNumber* BulletCnt = new DigitNumber();
		SetChild(BulletCnt);
	}

	AddComponent<WeaponBulletCount>();

	AddComponent<PlayerCtrl>();
	AddComponent<PlayerStateMachine>();
}

// EOF