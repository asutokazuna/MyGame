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

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Init()
{
	AddComponent<Object3D>()->SetModel(MODEL_PLAYER);
	AddComponent<PlayerMove>();
	m_col = AddComponent<PlayerCollision>();

	m_Missile = std::make_unique<PlayerMissile[]>(MAX_MISSILE);
	for (int i = 0; i < MAX_MISSILE; i++){
		m_Missile[i].Init();
	}
	HRESULT hr = S_OK;	
	
	return hr;
}

void CPlayer::Uninit()
{
	GameObject::Uninit();	
	for (int i = 0; i < MAX_MISSILE; i++) {
		m_Missile[i].Uninit();
	}
}

void CPlayer::Update()
{
	GameObject::Update();
	 //ミサイル発射
	if (CInput::GetKeyTrigger(VK_L)) {
		for (int i = 0; i < MAX_MISSILE; i++) {
			bool isShot = false;
			isShot = m_Missile[i].Fire(&transform->position, transform->quaternion);
			if (isShot == true) {
				break;
			}
		}
	}
	for (int i = 0; i < MAX_MISSILE; i++) {
		m_Missile[i].Update();
	}

}

void CPlayer::Draw()
{
	GameObject::Draw();	
	for (int i = 0; i < MAX_MISSILE; i++) {
		m_Missile[i].Draw();
	}
}

void CPlayer::DrawAlpha()
{
	GameObject::DrawAlpha();
}

// EOF