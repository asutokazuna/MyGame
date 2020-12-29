/**
 * @file CoreCollision
 * @brief CoreCollision�N���X
 */
#pragma once
#include "collision.h"

class CoreCollision :public Collision
{
protected:
	bool m_isInvincible;	//!< ���G���ǂ���
	int m_OpponentBulletTag;	//!< �_���[�W����̑���̎��ʔԍ�
	int m_OpponentTower;	//!< ����̃^���[�̎��ʔԍ�
public:
	CoreCollision();
	void Update();
	void OnCollisionEnter(GameObject* gameObj);
	void SetOpponentBullet(int kind);
	void SetOpponentTower(int kind);
};

// EOF