/**
 * @file CorePlayer.h
 * @brief 味方チームのコアクラス
 */
#include "CorePlayer.h"
#include "CoreCollision.h"
#include "TowerCtrl.h"

#define CORE_POS_Z (-600)

HRESULT CorePlayer::Init()
{
	Core::Init();
	tag = OBJ_TAG_CORE_PLAYER;

	transform->position.z = CORE_POS_Z;

	GetComponent<CoreCollision>()->SetOpponentBullet(OBJ_TAG_ENEMYMISSILE);
	GetComponent<CoreCollision>()->SetOpponentTower(TowerCtrl::TOWERSTATE::ENEMY);
	
	return E_NOTIMPL;
}

// EOF