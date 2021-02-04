/**
 * @file CorePlayerGauge
 * @brief 味方コアの残りHP表示コンポーネント
 */
#pragma once
#include "Component.h"
#include "CoreGauge.h"

/**
 * @class CorePlayerGauge
 * @brief 味方コアの残りHP表示コンポーネント
 */
class CorePlayerGauge :	public CoreGauge
{
public:
	void Awake();
	HRESULT Init();
};

// EOF