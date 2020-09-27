/**
 * @file Enemy
 * @brief エネミークラス
 * @date 2020/06/19
 */
#include "Enemy.h"
#include "CPlayer.h"
#include "input.h"
#include "Object3D.h"
#include "ModelData.h"
#include "EnemyCtrl.h"
#include "EnemyMissile.h"

 //*****************************************************************************
 // マクロ定義
 //*****************************************************************************
#define PATH_ENEMY		"data/model/X_wing.fbx"
#define SPEED			(5.0f)

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

HRESULT Enemy::Init()
{
	HRESULT hr = S_OK;	

	m_Missile = new EnemyMissile();

	AddComponent<Object3D>()->SetModel(MODEL_ENEMY);
	AddComponent<EnemyCtrl>();
	m_Missile->Init();

	return hr;
}

void Enemy::Uninit()
{
	m_Missile->Uninit();
	delete m_Missile;
	GameObject::Uninit();
}

void Enemy::Update()
{
	m_Missile->Fire(&transform->position, transform->quaternion);
	m_Missile->Update();
	GameObject::Update();
}

void Enemy::Draw()
{
	m_Missile->Draw();
	GameObject::Draw();
}

// EOF