/**
 * @file CPlayer
 * @brief プレイヤークラス
 * @date 2020/06/19
 */
#pragma once
#include "Box.h"
#include "GameObject.h"
#include <list>

// 前方宣言
class PlayerMissile;
class Collision;

/**
 * @class CPlayer
 * @brief プレイヤーのゲームオブジェクト
 */
class CPlayer: public GameObject
{
private:
	std::list<PlayerMissile*> m_Missile;	//!< ミサイル
	Collision* m_col;						//!< コライダー

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
};

// EOF