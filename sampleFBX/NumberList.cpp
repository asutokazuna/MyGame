/**
 * @file NumberList
 * @brief 文字表示オブジェクト
 */
#include "NumberList.h"
#include "DigitNumber.h"
#include "NumberListCtrl.h"

/**
 * @param num 桁数
 */
NumberList::NumberList(int num)
{
	for (int i = 0; i < num; i++)
	{
		DigitNumber* BulletCnt = new DigitNumber();
		SetChild(BulletCnt);
	}
}

void NumberList::Awake()
{
	AddComponent<NumberListCtrl>()->SetNumber(0);
}

// EOF