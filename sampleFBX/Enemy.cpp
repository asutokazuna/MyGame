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

/**
 * @brief 初期化処理
 * @return なし
 */
void Enemy::Awake()
{
	HRESULT hr = S_OK;	
	tag = OBJ_TAG_ENEMY;

	AddComponent<Object3D>()->SetModel(MODEL_ENEMY);
	AddComponent<EnemyCtrl>();

	m_Weapon = new Weapon(20);
	m_Weapon->SetTag(OBJ_TAG_ENEMYMISSILE);
	SetChild(m_Weapon);
}

// EOF