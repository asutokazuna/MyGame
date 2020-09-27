/**
 * @file Object.h
 * @brief �x�[�X�ƂȂ�I�u�W�F�N�g�N���X
 */
#pragma once
#include "main.h"

/**
 * @class Object
 * @breif �x�[�X�I�u�W�F�N�g
 */
class Object
{
protected:
	bool m_isActive;		//!< �A�N�e�B�u���ǂ���

public:
	/**
	 * @brief ������
	 * @return �Ȃ�
	 */
	static void Destroy(Object* obj);

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~Object();

	/**
	 * @brief ����������
	 * @return �Ȃ�
	 */
	virtual void Awake();

	/**
	 * @brief ����������
	 * @return�@�Ȃ�
	 */
	virtual HRESULT Init();

	/**
	 * @brief �I������
	 * @return�@�Ȃ�
	 */
	virtual void Uninit();

	/**
	 * @brief �X�V����
	 * @return�@�Ȃ�
	 */
	virtual void Update();

	/**
	 * @brief �X�V����
	 * @return�@�Ȃ�
	 */
	virtual void LateUpdate();

	/**
	 * @brief �`�揈��
	 * @return�@�Ȃ�
	 */
	virtual void Draw();

	/**
	 * @brief ���������`�揈��
	 * @return�@�Ȃ�
	 */
	virtual void DrawAlpha();

	/**
	 * @brief �L�����̐؂�ւ�
	 * @param[in] flg �I�u�W�F�N�g�̗L�����t���O
	 * @return �Ȃ�
	 */
	void SetActive(bool flg) {
		m_isActive = flg;
	}

};

// EOF