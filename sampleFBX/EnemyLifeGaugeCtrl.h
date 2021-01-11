#pragma once
#include "Component.h"

class EnemyLifeGaugeCtrl :public Component
{
public:
	HRESULT Init();
	void Update();
};

// EOF