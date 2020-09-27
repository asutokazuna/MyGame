/**
 * @file PlayerMissile
 * @brief プレイヤーミサイルクラス
 */
#pragma once
#include "Missile.h"
#include "Enemy.h"

class CExplosion;
class Transform;

class PlayerMissile: public Missile
{
private:

public:
	HRESULT Init();

};

// EOF