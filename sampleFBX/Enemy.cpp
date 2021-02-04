/**
 * @file Enemy
 * @brief エネミークラス
 * @date 2020/06/19
 */
#include "Enemy.h"
#include "Object3D.h"
#include "ModelData.h"
#include "EnemyCtrl.h"
#include "Weapon.h"
#include "collision.h"
#include "EnemyState.h"
#include "EnemyLifeCtrl.h"
#include "Gauge.h"
#include "EnemyLifeGaugeCtrl.h"
#include "ObjectManager.h"
#include "EnemyWeaponCtrl.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void Enemy::Awake()
{
	HRESULT hr = S_OK;	
	tag = OBJ_TAG_ENEMY;

	m_Weapon = //new Weapon(20);
		ObjectManager::Create<Weapon>("EnemyWeapon");
	m_Weapon->AddComponent<EnemyWeaponCtrl>();
	m_Weapon->SetTag(OBJ_TAG_ENEMYMISSILE);
	m_Weapon->SetParent(this);

	GameObject* gauge = //new Gauge();
		ObjectManager::Create<Gauge>("EnemyLifeGauge");
	gauge->SetParent(this);

	AddComponent<Object3D>()->SetModel(MODEL_ENEMY);
	AddComponent<Collision>()->SetModelKind(MODEL_ENEMY);
	AddComponent<EnemyCtrl>();
	AddComponent<EnemyLifeCtrl>();
	AddComponent<EnemyStateMachine>();
	AddComponent<EnemyLifeGaugeCtrl>();
}

// EOF