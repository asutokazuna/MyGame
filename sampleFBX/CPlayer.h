﻿/**
 * @file CPlayer
 * @brief プレイヤークラス
 * @date 2020/06/19
 */
#pragma once
#include "GameObject.h"
#include <list>
#include <memory>

// 前方宣言
class PlayerMissile;
class Collision;
class Weapon;

/**
 * @class CPlayer
 * @brief プレイヤーのゲームオブジェクト
 */
class CPlayer: public GameObject
{
private:
	Weapon* m_Weapon;
	Collision* m_col;						//!< コライダー

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
};

// EOF