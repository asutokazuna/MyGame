/**
 * @file NumberList
 * @brief 文字表示オブジェクト
 */
#include "NumberList.h"
#include "DigitNumber.h"
#include "NumberListCtrl.h"
//
///**
// * @brief コンストラクタ
// * @param[in] num 桁数
// */
//NumberList::NumberList(int num)
//{
//	for (int i = 0; i < num; i++)
//	{
//		DigitNumber* BulletCnt = new DigitNumber();
//		SetChild(BulletCnt);
//	}
//}

/**
 * @brief 初期化処理
 * @return なし
 */
void NumberList::Awake()
{
	AddComponent<NumberListCtrl>()->SetNumber(0);
}

// EOF