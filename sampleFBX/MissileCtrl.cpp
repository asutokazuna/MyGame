/**
 * @file MissileCtrl
 * @brief �e�̐���R���|�[�l���g
 */
#include "MissileCtrl.h"

/**
 * @brief ����������
 * @return �Ȃ�
 */
void MissileCtrl::Awake()
{
	m_power = 1;
}

/**
 * �e�̈З͂̎擾
 * @return �e�̈З�
 */
int MissileCtrl::GetPower()
{
	return m_power;
}

// EOF