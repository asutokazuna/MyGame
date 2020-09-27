/**
 * @file Enemy
 * @brief プレイヤークラス
 * @date 2020/06/19
 */
#pragma once

#include "main.h"
#include "GameObject.h"

class EnemyMissile;

class Enemy: public GameObject
{
private:
	EnemyMissile* m_Missile;
public:
	Enemy();
	~Enemy();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
};

// EOF