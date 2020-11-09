/**
 * @file Enemy
 * @brief 敵クラス
 * @date 2020/06/19
 */
#pragma once
#include "main.h"
#include "GameObject.h"

// 前方宣言
class Weapon;

/**
 * @class Enemy
 * @brief エネミークラス
 */
class Enemy: public GameObject
{
private:
	Weapon* m_Weapon;

public:

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
};

// EOF