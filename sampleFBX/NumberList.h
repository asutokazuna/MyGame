/**
 * @file NumberList
 * @brief 文字表示オブジェクト
 */
#pragma once
#include "GameObject.h"

// 前方宣言
class DigitNumber;

class NumberList :public GameObject
{
public:

	///**
	// * @brief コンストラクタ
	// * @param[in] num 桁数
	// */
	//NumberList(int num);

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
};

// EOF