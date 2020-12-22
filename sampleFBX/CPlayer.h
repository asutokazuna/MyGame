/**
 * @file CPlayer
 * @brief プレイヤークラス
 * @date 2020/06/19
 */
#pragma once
#include "GameObject.h"
#include <list>

// 前方宣言
class Collision;
class Weapon;
class DigitNumber;

/**
 * @class CPlayer
 * @brief プレイヤーのゲームオブジェクト
 */
class CPlayer: public GameObject
{
private:
	Weapon* m_Weapon;		//!< 武器
	Collision* m_col;		//!< コライダー

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
};

// EOF