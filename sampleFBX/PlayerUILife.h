/**
 * @class PlayerUILife
 * @breif �v���C���[�̃X�e�[�^�X��UI�ɕ\������R���|�[�l���g
 * @author Ariga
 */
#pragma once
#include "Component.h"

class GameObject;
class PlayerLifeCtrl;
class NumberListCtrl;

/**
 * @class PlayerUILife
 * @breif �v���C���[�̃X�e�[�^�X��UI�ɕ\������R���|�[�l���g
 */
class PlayerUILife :public Component
{
private:
	GameObject* m_playerObj;
	PlayerLifeCtrl* m_playerLife;
	GameObject* m_numberUI;
	GameObject* m_gauge;
	NumberListCtrl* m_LifeNum;

public:

	/**
	 * @brief ����������
	 * @return �Ȃ�
	 */
	HRESULT Init();

	/**
	 * @brief �X�V����
	 * @return �Ȃ�
	 */
	void Update();
};

// EOF