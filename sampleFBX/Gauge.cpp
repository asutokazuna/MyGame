/**
 * @file Gauge
 * @brief ゲージ表示クラス
 */
#include "Gauge.h"
#include "Billboard.h"

/**
 * @brief コンストラクタ
 */
Gauge::Gauge():m_Max(1),m_Min(0), m_Value(nullptr),m_offset(),m_transform(), m_myColor(), m_EnemyColor()
{
}

/**
 * @brief 初期化処理
 * @return なし
 */
void Gauge::Awake()
{
	m_bar = new GameObject();
	m_frame = new GameObject();
	SetChild(m_bar);
	SetChild(m_frame);
	m_frame->AddComponent<Billboard>()->ChangeSize(50, 50, 50)->ChangeColor(1, 1, 1);
	barmesh = m_bar->AddComponent<Billboard>()->ChangeSize(0, 50, 50)->ChangeColor(1, 0, 0);
}

/**
 * @brief 更新処理
 * @return なし
 */
void Gauge::Update()
{
	m_bar->GetTransform().position = m_transform->position + m_offset;
	m_frame->GetTransform().position = m_transform->position + m_offset;
	float sizeY = (*m_Value - (m_Max / 2)) / (m_Max / 2);
	Vector3 color = Vector3();
	if (sizeY > 0) {
		color = m_myColor;
	}
	else {
		color = m_EnemyColor;
	}
	sizeY = abs(sizeY);
	barmesh->ChangeSize(50 * sizeY, 50, 50)->ChangeColor(color);
	GameObject::Update();
}

void Gauge::SetParam(float max, float min, Vector3 myColor, Vector3 enemyColor)
{
	m_Max = max;
	m_Min = min;
	m_myColor = myColor;
	m_EnemyColor = enemyColor;
}

void Gauge::SetValue(int& value)
{
	m_Value = &value;
}

void Gauge::SetTransform(Transform * trans)
{
	m_transform = trans;
}

void Gauge::SetOffset(Vector3 value)
{
	m_offset = value;
}

// EOF