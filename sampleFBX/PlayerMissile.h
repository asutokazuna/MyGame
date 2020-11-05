/**
 * @file PlayerMissile
 * @brief プレイヤーミサイルクラス
 */
#pragma once
#include "Missile.h"
#include "Enemy.h"

// 前方宣言
class CExplosion;
class Transform;

/**
 * @class PlayerMissile
 * @brief プレイヤーのミサイル
 */
class PlayerMissile: public Missile
{
private:

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

};

// EOF