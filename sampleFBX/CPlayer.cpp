/**
 * @file CPlayer
 * @brief プレイヤークラス
 * @date 2020/06/19
 */
#include "CPlayer.h"
#include "PlayerMissile.h"
#include "Object3D.h"
#include "PlayerMove.h"
#include "PlayerCollision.h"
#include "PlayerCtrl.h"
#include "Rigidbody.h"

/**
 * @def
 */
#define MAX_MISSILE		(5)

/**
 * @brief 初期化処理
 * @return なし
 */
void CPlayer::Awake()
{
	transform->position.z = -500;
	tag = OBJ_TAG_PLAYER;

	AddComponent<PlayerMove>();
	AddComponent<Rigidbody>();
	AddComponent<Object3D>()->SetModel(MODEL_PLAYER);
	m_col = AddComponent<Collision>();
	m_col->SetModelKind(MODEL_PLAYER);

	for (int i = 0; i < MAX_MISSILE; i++) {
		PlayerMissile* temp = new PlayerMissile();
		m_Missile.push_back(temp);
		SetChild(temp);
	}

	AddComponent<PlayerCtrl>()->InitParam(m_Missile);
}

// EOF