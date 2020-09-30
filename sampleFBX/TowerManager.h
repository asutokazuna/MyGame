/**
 * @file TowerManager
 * @brief タワー管理クラス
 */
#pragma once
#include "GameObject.h"

class Tower;

class TowerManager: public GameObject
{
private:
	Tower* m_Tower;
public:
	static int m_isAttack;
public:
	TowerManager();
	~TowerManager();
	void Awake();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void DrawAlpha();

	bool IsAttackPlayerCore();
	bool IsAttackEnemyCpre();
};

// EOF