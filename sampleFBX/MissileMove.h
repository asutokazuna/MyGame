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
	int m_Speed;
public:
	MissileMove();
	~MissileMove();

	HRESULT Init();
	void Update();
};

// EOF