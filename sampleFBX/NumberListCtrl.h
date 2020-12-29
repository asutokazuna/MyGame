/**
 * @file NumberListCtrl
 * @brief 数字表示コンポーネント
 */
#pragma once
#include "Component.h"
#include <list>
#include "MyMath.h"

// 前方宣言
class DigitNumber;

/**
 * @class NumberListCtrl
 * @brief 数字列管理クラス
 */
class NumberListCtrl :public Component
{
private:
	std::list<DigitNumber*> m_NumberList;
	float m_width;

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT Init();

	/**
	 * @brief 数字のセット
	 * @param[in] セットする数字
	 * @return なし
	 */
	void SetNumber(int num);

	/**
	 * @brief 座標の設定
	 * @param[in] pos 設定座標
	 * @return なし
	 */
	void SetPos(Vector3 pos);

	/**
	 * @brief 数字同士の幅の設定
	 * @param[in] width 幅
	 * @return なし
	 */
	void SetWidth(float width);
};

// EOF