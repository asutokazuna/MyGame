/**
 * @file PlayerMissile
 * @brief �v���C���[�~�T�C���N���X
 */
#pragma once
#include "Missile.h"
#include "Enemy.h"

class CExplosion;
class Transform;
class PlayerMissile: public Missile
{
private:
	CExplosion* m_exp;		//!< �����G�t�F�N�g

public:
	PlayerMissile();
	~PlayerMissile();
	HRESULT Init();

};

// EOF