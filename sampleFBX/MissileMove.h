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
	int m_nStat;			//!< 0:未使用, 1:使用中
	int m_nLife;			//!< 寿命
	float m_Speed;
public:
	MissileMove();

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT Init();
	void Update();
};

// EOF