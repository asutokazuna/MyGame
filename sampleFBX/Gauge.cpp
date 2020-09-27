/**
 * @file Gauge
 * @brief ゲージ表示クラス
 */
#include "Gauge.h"
#include "Billboard.h"
#include "TowerEnergy.h"


Gauge::Gauge():m_Max(ENERGY_MAX / (float)2),m_Min(0),m_Value(20),m_offset(),m_transform()
{
}

HRESULT Gauge::Init()
{
	m_bar = new GameObject();
	m_frame = new GameObject();
	m_frame->AddComponent<Billboard>()->ChangeSize(50, 50, 50)->ChangeColor(1, 1, 1);
	barmesh = m_bar->AddComponent<Billboard>()->ChangeSize(0, 50, 50)->ChangeColor(1, 0, 0);

	return E_NOTIMPL;
}

void Gauge::Uninit()
{
	m_bar->Uninit();
	m_frame->Uninit();
	delete m_frame;
	delete m_bar;
	GameObject::Uninit();
}

void Gauge::Update()
{
	m_bar->GetTransform().position = m_transform.position + m_offset;
	m_frame->GetTransform().position = m_transform.position + m_offset;
	float sizeY = (m_Value -20) / m_Max;
	sizeY = abs(sizeY);
	XMFLOAT3 color = XMFLOAT3();
	if (m_Value > ENERGY_MAX / (float)2) {
		color = XMFLOAT3(0, 1, 0);
	}
	else if (m_Value < ENERGY_MAX / (float)2) {
		color = XMFLOAT3(1, 0, 0);
	}
	barmesh->ChangeSize(50 * sizeY, 50, 50)->ChangeColor(color);
	GameObject::Update();
}

void Gauge::Draw()
{
	m_bar->Draw();
	m_frame->Draw();
	GameObject::Draw();
}

void Gauge::SetParam(float max, float min)
{
	m_Max = max;
	m_Min = min;
}

void Gauge::SetValue(float value)
{
	m_Value = value;
}

void Gauge::SetTransform(Transform & trans)
{
	m_transform = trans;
}

void Gauge::SetOffset(Vector3 value)
{
	m_offset = value;
}
