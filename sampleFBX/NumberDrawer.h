/**
 * @file NumberDrawer
 * @brief 1数字表示コンポーネント
 */
#pragma once
#include "Component.h"

class DefaultShaderInfo;

/**
 * @class 
 * @brief 
 */
class NumberDrawer :public Component
{
private:
	int num;
	DefaultShaderInfo* m_shader;
public:

	/**
	 * @brief コンストラクタ
	 */
	NumberDrawer();

	void Awake();

	/**
	 * @brief 初期化処理
	 * @retrun なし
	 */
	//HRESULT Init();

	/**
	 * @brief 数字のセット
	 * @return なし
	 */
	void SetNumber(int num);
};

// EOF