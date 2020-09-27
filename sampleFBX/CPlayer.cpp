/**
 * @file CPlayer
 * @brief プレイヤークラス
 * @date 2020/06/19
 */
#include "CPlayer.h"
#include "input.h"
#include "CCamera.h"
#include "PlayerMissile.h"
#include "Object3D.h"
#include "PlayerMove.h"
#include "PlayerCollision.h"
#include "Billboard.h"

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

	AddComponent<Object3D>()->SetModel(MODEL_PLAYER);
	AddComponent<PlayerMove>();
	m_col = AddComponent<PlayerCollision>();
}

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT CPlayer::Init()
{

	HRESULT hr = S_OK;	
	
	return hr;
}

/**
 * @brief 更新処理
 * @return なし
 */
void CPlayer::Update()
{
	GameObject::Update();
	 //ミサイル発射
	if (CInput::GetKeyTrigger(VK_L)) {
		for (auto m : m_Missile) {
			bool flg = false;
			flg = m->Fire(&transform->position, transform->quaternion);
			if (flg == true) {
				break;
			}
		}
	}
}

// EOF