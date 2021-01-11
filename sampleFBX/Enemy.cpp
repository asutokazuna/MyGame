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

/**
 * @brief 初期化処理
 * @return なし
 */
void Enemy::Awake()
{
	HRESULT hr = S_OK;	
	tag = OBJ_TAG_ENEMY;

	AddComponent<Object3D>()->SetModel(MODEL_ENEMY);
	AddComponent<Collision>()->SetModelKind(MODEL_ENEMY);
	AddComponent<EnemyCtrl>();
	AddComponent<EnemyLifeCtrl>();
	AddComponent<EnemyStateMachine>();
	AddComponent<EnemyLifeGaugeCtrl>();

	m_Weapon = new Weapon(20);
	m_Weapon->SetTag(OBJ_TAG_ENEMYMISSILE);
	SetChild(m_Weapon);

	GameObject* gauge = new Gauge();
	gauge->SetName("LifeGauge");
	SetChild(gauge);
}

// EOF