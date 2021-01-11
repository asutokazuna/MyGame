/**
 * @file PlayerSpawner
 * @brief プレイヤーの生成管理オブジェクト
 */
#pragma once
#include "CharacterSpawner.h"

 /**
  * @file PlayerSpawner
  * @brief プレイヤーの生成管理オブジェクト
  */
class PlayerSpawner :public CharacterSpawner
{
public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
};

// EOF