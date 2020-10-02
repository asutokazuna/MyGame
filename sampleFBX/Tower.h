/**
 * @file Tower
 * @brief Towerクラス
 */
#pragma once
#include "GameObject.h"

// 前方宣言
class Object3D;
class TowerEnergy;
struct TFbxMaterial;
class Collision;
class Gauge;

/**
 * @class Tower
 * @brief タワー
 */
class Tower :public GameObject
{
private:
	Object3D* m_Object3D;
	XMFLOAT3 color;
	TFbxMaterial* material;
	Collision* m_collision;
	Gauge*	m_LifeGauge;
public:
	TowerEnergy* m_Energy;

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	void Uninit();
	void Update();
	void Draw();
	void ChangeColor();
	Tower* SetPos(Vector3 pos);
};

// EOF