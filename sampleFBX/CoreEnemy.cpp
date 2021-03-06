﻿/**
 * @file CoreEnemy.h
 * @brief 敵チームのコアクラス
 */
#include "CoreEnemy.h"
#include "CoreCollision.h"
#include "TowerCtrl.h"

#define CORE_POS_Z (600)

void CoreEnemy::Awake()
{
	Core::Awake();
	tag = OBJ_TAG_CORE_ENEMY;
	transform->position.z = CORE_POS_Z;
}

HRESULT CoreEnemy::Init()
{
	Core::Init();

	GetComponent<CoreCollision>()->SetOpponentBullet(OBJ_TAG_PLAYERMISSILE);
	GetComponent<CoreCollision>()->SetOpponentTower(TowerCtrl::TOWERSTATE::PLAYER);

	return E_NOTIMPL;
}

// EOF