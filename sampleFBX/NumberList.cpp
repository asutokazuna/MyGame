/**
 * @file NumberList
 * @brief �����\���I�u�W�F�N�g
 */
#include "NumberList.h"
#include "DigitNumber.h"
#include "NumberListCtrl.h"

/**
 * @brief �R���X�g���N�^
 * @param[in] num ����
 */
NumberList::NumberList(int num)
{
	for (int i = 0; i < num; i++)
	{
		DigitNumber* BulletCnt = new DigitNumber();
		SetChild(BulletCnt);
	}
}

/**
 * @brief ����������
 * @return �Ȃ�
 */
void NumberList::Awake()
{
	AddComponent<NumberListCtrl>()->SetNumber(0);
}

// EOF