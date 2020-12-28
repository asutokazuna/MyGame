/**
 * @file PlayerLifeUI
 * @brief HP�̕\��
 */
#pragma once
#include "Component.h"
#include <list>

class PlayerLifeCtrl;

/**
 * @class PlayerLifeUI
 * @brief HP�̕\��
 */
class PlayerLifeUI :public Component
{
private:
	std::list<GameObject*> m_NumberList;		//!< ���C�t�\���I�u�W�F�N�g
	PlayerLifeCtrl* m_lifeCtrl;
public:
	/**
	 * @brief ����������
	 * @return �Ȃ�
	 */
	void Awake();

	/**
	 * @brief �X�V����
	 * @return �Ȃ�
	 */
	void Update();
};

// EOF