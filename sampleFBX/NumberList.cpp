/**
 * @file NumberList
 * @brief 文字表示オブジェクト
 * @author Ariga
 */
#include "NumberList.h"
#include "NumberListCtrl.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void NumberList::Awake()
{
	AddComponent<NumberListCtrl>()->SetNumber(0);
}

// EOF