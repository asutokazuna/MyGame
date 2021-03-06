﻿/**
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
#include "PlayerLifeCtrl.h"
#include "NumberList.h"
#include "GaugeUI.h"
#include "ObjectManager.h"
#include "PlayerWeaponCtrl.h"
#include "PlayerUILife.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void CPlayer::Awake()
{
	tag = OBJ_TAG_PLAYER;

	AddComponent<PlayerMove>();
	//AddComponent<Rigidbody>();
	AddComponent<Object3D>()->SetModel(MODEL_PLAYER);
	m_col = AddComponent<Collision>();
	m_col->SetModelKind(MODEL_PLAYER);

	// 武器
	m_Weapon = //new Weapon(30);
		ObjectManager::Create<Weapon>("Weapon");
	m_Weapon->AddComponent<PlayerWeaponCtrl>();
	m_Weapon->SetTag(OBJ_TAG_PLAYERMISSILE);
	m_Weapon->SetParent(this);

	// ロックオン
	GameObject* obj = ObjectManager::Create<Lockon>("Lockon");
	obj->SetParent(this);
	
	// 残弾数
	NumberList* m_bulletUI =// new NumberList(2);
	ObjectManager::Create<NumberList>("BulletUI");
	m_bulletUI->SetParent(this);
	
	// UIの管理部分オブジェクト
	GameObject* m_playerUI = ObjectManager::Create<NumberList>("PlayerUI");
	m_playerUI->AddComponent<PlayerUILife>();

	// HPの表示(数字)オブジェクト
	NumberList* m_numberUI = //new NumberList(3);
		ObjectManager::Create<NumberList>("PlayerLifeUI");
	m_numberUI->SetParent(m_playerUI);
	
	// HPゲージ表示オブジェクト
	GameObject* m_gaugeLife = //new GaugeUI();
		ObjectManager::Create<GaugeUI>("LifeGauge");
	m_gaugeLife->SetParent(m_playerUI);

	AddComponent<PlayerShotDir>();
	AddComponent<PlayerCtrl>();
	AddComponent<PlayerLifeCtrl>();
	AddComponent<WeaponBulletCount>();
	AddComponent<PlayerStateMachine>();
}

// EOF