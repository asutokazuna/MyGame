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
	for (int i = 0; i < MAX_MISSILE; i++) {
		PlayerMissile* temp = new PlayerMissile();
		m_Missile.push_back(temp);
		SetChild(temp);
	}
	transform->position.z = -500;

	AddComponent<Object3D>()->SetModel(MODEL_PLAYER);
	AddComponent<PlayerMove>();
	m_col = AddComponent<PlayerCollision>();
	AddComponent<PlayerCtrl>()->InitParam(m_Missile);
	AddComponent<Rigidbody>();
}

// EOF