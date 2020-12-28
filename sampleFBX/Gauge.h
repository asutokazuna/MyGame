/**
 * @file Gauge
 * @brief ゲージ表示クラス
 */
#pragma once
#include "GameObject.h"
#include "MyMath.h"

// 前方宣言
class Mesh;

/**
 * @class Gauge
 * @brief ゲージ
 */
class Gauge :public GameObject
{
private:
	float m_Min;
	float m_Max;
	int* m_Value;

	GameObject* m_LifeGauge;
	GameObject* m_frame;
	Transform* m_transform;

	Mesh* barmesh;
	Vector3 m_myColor;
	Vector3 m_EnemyColor;
	Vector3 m_offset;
public:

	/**
	 * @brief コンストラクタ
	 */
	Gauge();

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
};

// EOF