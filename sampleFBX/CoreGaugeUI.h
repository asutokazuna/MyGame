/**
 * @file CoreGaugeUI
 * @brief コアのHPゲージ表示UIオブジェクト
 */
#pragma once
#include "GameObject.h"

/**
 * @class CoreGaugeUI
 * @brief コアのHPゲージ表示UIオブジェクト
 */
class CoreGaugeUI :public GameObject
{
public:
	/**
	 * @breif 初期化処理
	 * @return なし
	 */
	void Awake();
};

// EOF