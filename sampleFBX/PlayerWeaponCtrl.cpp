/**
 * @file PlayerWeaponCtrl 
 * @brief プレイヤーの武器の制御コンポーネント
 */
#include "PlayerWeaponCtrl.h"
#include "WeaponCtrl.h"
#include "GameObject.h"
#include <list>
#include "collision.h"

#define MAX_BULLET (30)

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT PlayerWeaponCtrl::Init()
{
	// 弾を発射できる数分のセット
	m_Parent->GetComponent<WeaponCtrl>()->SetMaxBullet(MAX_BULLET);
	std::list<GameObject*> *missileList = m_Parent->GetComponent<WeaponCtrl>()->GetMissileList();

	for (auto missile : *missileList)
	{
		missile->SetTag(OBJ_TAG_PLAYERMISSILE);
	}

	return E_NOTIMPL;
}

// EOF