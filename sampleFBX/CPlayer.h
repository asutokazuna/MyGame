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

// �O���錾
class PlayerMissile;
class Collision;

/**
 * @class CPlayer
 * @brief �v���C���[�̃Q�[���I�u�W�F�N�g
 */
class CPlayer: public GameObject
{
private:
	XMFLOAT3 m_vCenter;		//!< ���E�{�b�N�X���S���W
	XMFLOAT3 m_vBBox;		//!< ���E�{�b�N�X�T�C�Y
	CBox m_box;				//!< ���E�{�b�N�X
private:
	std::list<PlayerMissile*> m_Missile;	//!< �~�T�C��
	Collision* m_col;						//!< �R���C�_�[

public:
	/**
	 * @brief ����������
	 * @return �Ȃ�
	 */
	void Awake();

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