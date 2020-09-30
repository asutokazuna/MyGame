/**
 * @file EnemyMissile
 * @brief 敵ミサイル
 */
#pragma once
#include "Missile.h"

class EnemyMissile :public Missile
{
public:
	HRESULT Init();
};

// EOF