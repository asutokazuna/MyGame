/**
 * @file CoreEnemy.h
 * @brief 敵チームのコアクラス
 */
#pragma once
#include "Core.h"

class CoreEnemy :public Core
{
public:
	void Awake();
	HRESULT Init();
};

// EOF