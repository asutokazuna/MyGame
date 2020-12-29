/**
 * @file MissileCtrl
 * @brief �e�̐���R���|�[�l���g
 */
#pragma once
#include "Component.h"

/**
 * @class MissileCtrl
 * @brief �e�̐���
 */
class MissileCtrl :public Component
{
protected:
	int m_power;		//!< �e�̈З�

public:
	/**
	 * @brief ����������
	 * @return �Ȃ�
	 */
	virtual void Awake();

	/**
	 * �e�̈З͂̎擾
	 * @return �e�̈З�
	 */
	virtual int GetPower();
};

// EOF