#include "NumberListCtrl.h"
#include "GameObject.h"
#include "DigitNumber.h"
#include "NumberDrawer.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void NumberListCtrl::Awake()
{
	m_width = 35;
	m_NumberList = m_Parent->GetChildren<DigitNumber>();
}

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT NumberListCtrl::Init()
{

	return E_NOTIMPL;
}

/**
 * @brief 数字のセット
 * @param[in] セットする数字
 * @return なし
 */
void NumberListCtrl::SetNumber(int num)
{
	int work = num;
	int value = 0;

	for (auto obj : m_NumberList)
	{
		value = work % 10;
		obj->GetComponent<NumberDrawer>()->SetNumber(value);
		work /= 10;
	}
}

/**
 * @brief 座標の設定
 * @param[in] pos 設定座標
 * @return なし
 */
void NumberListCtrl::SetPos(Vector3 pos)
{
	int i = 0;
	Vector3 scale = Vector3();
	for (auto o : m_NumberList)
	{
		scale = o->GetTransform().scale;
		o->GetTransform().position = Vector3(pos.x - m_width * i, pos.y, pos.z);
		i++;
	}
}

/**
 * @brief 数字同士の幅の設定
 * @param[in] width 幅
 * @return なし
 */
void NumberListCtrl::SetWidth(float width)
{
	m_width = width;
}

// EOF