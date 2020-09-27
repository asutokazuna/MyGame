/**
 * @file CPlayer
 * @brief �v���C���[�N���X
 * @date 2020/06/19
 */
#pragma once

#include "Box.h"
#include "GameObject.h"
#include <memory>
#include <list>

class PlayerMissile;
class Collision;

class CPlayer: public GameObject
{
private:
	XMFLOAT3 m_vCenter;		//!< ���E�{�b�N�X���S���W
	XMFLOAT3 m_vBBox;		//!< ���E�{�b�N�X�T�C�Y
	CBox m_box;				//!< ���E�{�b�N�X

	XMFLOAT3 m_vPosBBox;	//!< ���E�{�b�N�X���S���W�i�j
	bool m_bHit;			//!< �Փ˂̗L��

private:
	std::list<PlayerMissile*> m_Missile;
	Collision* m_col;

public:
	CPlayer();
	HRESULT Init();
	void Update();
};

// EOF