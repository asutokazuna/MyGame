/**
 * @file NumberListCtrl
 * @brief �����\���R���|�[�l���g
 */
#pragma once
#include "Component.h"
#include <list>
#include "MyMath.h"

// �O���錾
class DigitNumber;

/**
 * @class NumberListCtrl
 * @brief ������Ǘ��N���X
 */
class NumberListCtrl :public Component
{
private:
	std::list<DigitNumber*> m_NumberList;
	float m_width;

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
	 * @brief �����̃Z�b�g
	 * @param[in] �Z�b�g���鐔��
	 * @return �Ȃ�
	 */
	void SetNumber(int num);

	/**
	 * @brief ���W�̐ݒ�
	 * @param[in] pos �ݒ���W
	 * @return �Ȃ�
	 */
	void SetPos(Vector3 pos);

	/**
	 * @brief �������m�̕��̐ݒ�
	 * @param[in] width ��
	 * @return �Ȃ�
	 */
	void SetWidth(float width);
};

// EOF