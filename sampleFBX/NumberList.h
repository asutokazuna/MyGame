/**
 * @file NumberList
 * @brief �����\���I�u�W�F�N�g
 */
#pragma once
#include "GameObject.h"

// �O���錾
class DigitNumber;

class NumberList :public GameObject
{
public:

	/**
	 * @brief �R���X�g���N�^
	 * @param[in] num ����
	 */
	NumberList(int num);

	/**
	 * @brief ����������
	 * @return �Ȃ�
	 */
	void Awake();
};

// EOF