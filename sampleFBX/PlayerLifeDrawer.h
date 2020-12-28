/**
 * @file PlayerLifeDrawer
 * @brief プレイヤーのHPの表示
 */
#pragma once
#include "GameObject.h"

/**
 * @class PlayerLifeDrawer
 */
class PlayerLifeDrawer :public GameObject
{
public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
};

// EOF