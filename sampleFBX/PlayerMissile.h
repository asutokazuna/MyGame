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
	CExplosion* m_exp;		//!< 爆発エフェクト

public:
	PlayerMissile();
	~PlayerMissile();
	HRESULT Init();

};

// EOF