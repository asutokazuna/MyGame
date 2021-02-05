/**
 * @file NumberListCtrl
 * @brief 数字表示コンポーネント
 */
#include "NumberListCtrl.h"
#include "GameObject.h"
#include "DigitNumber.h"
#include "NumberDrawer.h"
#include "ObjectManager.h"

/**
 * @brief 数字の桁数を数える
 * @param num 数字
 * @return なし
 */
int CountNumber(int num)
{
	int cnt = 0;
	while (num > 0)
	{
		num /= 10;
		cnt++;
	}
	return cnt;
}

void NumberListCtrl::UpdatePos()
{
	int i = 0;
	Vector3 scale = Vector3();
	for (auto o : m_NumberList)
	{
		//scale = o->GetTransform().scale;
		o->GetTransform().position = Vector3(pos.x - m_width * i, pos.y, pos.z);
		i++;
	}
}

/**
 * @brief 初期化処理
 * @return なし
 */
void NumberListCtrl::Awake()
{
	m_width = 35;
	pos = Vector3();
	//m_NumberList = m_Parent->GetChildren<DigitNumber>();
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
	int cnt = CountNumber(num);
	DigitNumber* number;

	Vector3 pos;

	// 桁数分のリストを作成
	while (m_NumberList.size() < cnt)
	{
		number = ObjectManager::Create<DigitNumber>("number");
		m_NumberList.push_back(number);
		number->SetParent(m_Parent);
		//SetPos(m_NumberList.front()->GetTransform().position);
	}

	if (m_NumberList.size() > 0) {
		UpdatePos();
	}

	// 数字を更新
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
	this->pos = pos;
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