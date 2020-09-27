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

 //*****************************************************************************
 // マクロ定義
 //*****************************************************************************
#define SPEED			(5.0f)
#define MAX_MISSILE		(5)

CPlayer::CPlayer()
{
	m_bHit = false;
}

HRESULT CPlayer::Init()
{
	AddComponent<Object3D>()->SetModel(MODEL_PLAYER);
	AddComponent<PlayerMove>();
	m_col = AddComponent<PlayerCollision>();

	for (int i = 0; i < MAX_MISSILE; i++){
		PlayerMissile* temp = new PlayerMissile();
		m_Missile.push_back(temp);
       	SetChild(temp);
	}
	HRESULT hr = S_OK;	
	
	return hr;
}

void CPlayer::Update()
{
	GameObject::Update();
	 //ミサイル発射
	if (CInput::GetKeyTrigger(VK_L)) {
		for (int i = 0; i < MAX_MISSILE; i++) {
			bool isShot = false;
//			isShot = m_Missile[i].Fire(&transform->position, transform->quaternion);
			if (isShot == true) {
				break;
			}
		}
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