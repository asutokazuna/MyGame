/**
 * @file PlayerMissile
 * @brief �v���C���[�~�T�C���N���X
 */
#pragma once
#include "Missile.h"
#include "Enemy.h"

class CExplosion;
class Transform;

/**
 * @class PlayerMissile
 * @brief �v���C���[�̃~�T�C��
 */
class PlayerMissile: public Missile
{
private:

public:
	HRESULT Init();

};

// EOF