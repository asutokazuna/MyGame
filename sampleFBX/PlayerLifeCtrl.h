/**
 * @class PlayerLifeCtrl
 * @brief �v���C���[��HP�̊Ǘ�
 */
#pragma once
#include "Component.h"

class NumberList;

/**
 * @class PlayerLifeCtrl
 * @brief �v���C���[��HP�̊Ǘ�
 */
class PlayerLifeCtrl :public Component
{
private:
	unsigned int m_Life;		//!< HP
	NumberList* m_numberUI;

public:
	/**
	 * @brief ����������
	 * @return �Ȃ�
	 */
	void Awake();

	HRESULT Init();

	/**
	 * @brief �X�V����
	 * @return �Ȃ�
	 */
	void Update();

	void  OnCollisionEnter(GameObject* gameObbj);
	/**
	 * @brief HP�̎擾
	 * @return ����HP�̎擾
	 */
	unsigned int GetLife();
};

// EOF