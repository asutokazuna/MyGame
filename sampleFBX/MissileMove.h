/**
 * @file MissileMove
 * @brief ミサイルの動きクラス
 */
#pragma once
#include "Component.h"

class Transform;

class MissileMove :public Component
{
private:
	Transform* m_transform;

public:
	float m_Speed;		//!< 弾の移動速度

public:

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT Init();
	void Update();
};

// EOF