/**
 * @file Tower
 * @brief Towerクラス
 */
#pragma once
#include "GameObject.h"

// 前方宣言
class Object3D;
class TowerEnergy;
class Collision;
class Gauge;
class TowerCtrl;

/**
 * @class Tower
 * @brief タワー
 */
class Tower :public GameObject
{
private:
	Object3D* m_Object3D;
	XMFLOAT3 color;
	Collision* m_collision;
	Gauge*	m_LifeGauge;
	TowerCtrl* m_ctrl;

public:
	TowerEnergy* m_Energy;

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT Init();
};

// EOF