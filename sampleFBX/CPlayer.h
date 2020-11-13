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
class Cube;

/**
 * @class CPlayer
 * @brief プレイヤーのゲームオブジェクト
 */
class CPlayer: public GameObject
{
private:
	Weapon* m_Weapon;		//!< 武器
	Collision* m_col;		//!< コライダー
	Cube* m_ShotCol;		//!< カーソルの当たり判定

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
};

// EOF