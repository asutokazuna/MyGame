/**
 * @file Enemy
 * @brief エネミークラス
 * @date 2020/06/19
 */
#include "Enemy.h"
#include "Object3D.h"
#include "ModelData.h"
#include "EnemyCtrl.h"
#include "EnemyMissile.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void Enemy::Awake()
{
	HRESULT hr = S_OK;	

	m_Missile = new EnemyMissile();

	AddComponent<Object3D>()->SetModel(MODEL_ENEMY);
	AddComponent<EnemyCtrl>();
	SetChild(m_Missile);
}

//void Enemy::Update()
//{
//	//m_Missile->Fire(&transform->position, transform->quaternion);
//	m_Missile->Update();
//	GameObject::Update();
//}

// EOF