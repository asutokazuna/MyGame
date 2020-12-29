/**
 * @file NumberDrawer
 * @brief 1数字表示コンポーネント
 */
#include "NumberDrawer.h"
#include "GameObject.h"
#include "DefaultShaderInfo.h"

/**
 * @brief コンストラクタ
 */
NumberDrawer::NumberDrawer():num(0)
{
}

/**
 * @brief 初期化処理
 * @retrun なし
 */
void NumberDrawer::Awake()
{
	m_shader = m_Parent->GetComponent<DefaultShaderInfo>();

	m_shader->SetUV(Vector3(num / (float)10, 1, 1), Vector3(1 / (float)10, 1, 1));
}

/**
 * @brief 数字のセット
 * @return なし
 */
void NumberDrawer::SetNumber(int num)
{
	this->num = num;
	// UV移動
	m_shader->SetUV(Vector3(num / (float)10, 1, 0), Vector3(1 / (float)10, 1, 1));
}

// EOF