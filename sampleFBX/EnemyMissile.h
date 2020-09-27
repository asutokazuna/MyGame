#pragma once
#include "Missile.h"

class EnemyMissile :public Missile
{
public:
	EnemyMissile();
	~EnemyMissile();
	HRESULT Init();
};

// EOF