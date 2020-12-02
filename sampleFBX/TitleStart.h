/**
 * @file TitleStart
 * @brief タイトルのスタートボタン
 */
#pragma once
#include "GameObject.h"

class Mesh;

/**
 * @class TitleStart
 */
class TitleStart :public GameObject
{
private:
	Mesh* m_mesh;
	float m_add;
	Vector3 m_color;
	float m_alpha;
public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 更新
	 * @return なし
	 */
	void Update();
};

// EOF