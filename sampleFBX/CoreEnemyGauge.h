/**
 * @file CoreEnemyGauge
 * @brief 敵コアの残りHP表示コンポーネント
 */
#pragma once
#include "Component.h"
#include "CoreGauge.h"

 /**
  * @class CoreEnemyGauge
  * @brief 敵コアの残りHP表示コンポーネント
  */
class CoreEnemyGauge :public CoreGauge
{
public:
	void Awake();
	HRESULT Init();
};

// EOF