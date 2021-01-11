/**
 * @class EnemyLifeCtrl
 * @brief �G��HP�̊Ǘ��R���|�[�l���g
 */
#pragma once
#include "Component.h"

/**
 * @class EnemyLifeCtrl
 * @brief �G��HP�̊Ǘ��R���|�[�l���g
 */
class EnemyLifeCtrl :public Component
{
private:
	int m_Life;		//!< HP
public:
	/**
	 * @brief ����������
	 * @return �Ȃ�
	 */
	HRESULT Init();

	/**
	 * @brief �����������̏���
	 * @return �Ȃ�
	 */
	void  OnCollisionEnter(GameObject* gameObj);
	/**
	 * @brief HP�̎擾
	 * @return ����HP�̎擾
	 */
	int GetLife();
	float GetLifePercent();
};

// EOF