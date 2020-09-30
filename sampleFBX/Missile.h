/**
 * @file Missile
 * @brief ミサイルクラス
 * @date 2020/06/19
 */
#pragma once
#include "main.h"
#include "Box.h"
#include "GameObject.h"

// 前方宣言
class Collision;
class MissileMove;

/**
 * @class Missile
 * @brief ミサイルクラスr
 */
class Missile: public GameObject
{
protected:
	Collision* m_col;
	MissileMove* m_Move;
public:
	Missile();

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
	void Update();
	void Draw();
	void DrawAlpha();

	bool Fire(Vector3* pos);
	bool Fire(Vector3* pos, Quaternion quat);
};

// EOF