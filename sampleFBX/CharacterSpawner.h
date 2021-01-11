/**
 * @file CharacterSpawner
 * @brief キャラの生成管理オブジェクト
 */
#pragma once
#include "GameObject.h"

/**
 * @brief CharacterSpawner
 * @brief キャラの生成管理オブジェクト
 */
class CharacterSpawner :public GameObject
{
public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	virtual void Awake();
};

// EOF