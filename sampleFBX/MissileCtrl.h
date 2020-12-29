/**
 * @file MissileCtrl
 * @brief 弾の制御コンポーネント
 */
#pragma once
#include "Component.h"

/**
 * @class MissileCtrl
 * @brief 弾の制御
 */
class MissileCtrl :public Component
{
protected:
	int m_power;		//!< 弾の威力

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	virtual void Awake();

	/**
	 * 弾の威力の取得
	 * @return 弾の威力
	 */
	virtual int GetPower();
};

// EOF