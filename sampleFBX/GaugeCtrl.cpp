#include "GaugeCtrl.h"
#include "GameObject.h"
#include "LifeGauge.h"
#include "LifeGaugeShaderInfo.h"
#include "DefaultShaderInfo.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void GaugeCtrl::Awake()
{
	m_target = nullptr;
	m_offset = Vector3();
	m_size = Vector3();

	m_frame = m_Parent->GetChildTest("frame");
	m_LifeGauge = m_Parent->GetChildTest("LifeGauge");
}

HRESULT GaugeCtrl::Init()
{

	return S_OK;
}

void GaugeCtrl::Update()
{
	Vector3 pos = Vector3();
	if (m_target != nullptr) {
		pos = m_target->position;
	}
	pos += m_offset;

	m_frame->GetTransform().position = pos;
	m_LifeGauge->GetTransform().position = pos;
	m_frame->GetTransform().scale = m_size;
	m_LifeGauge->GetTransform().scale = m_size;
}

void GaugeCtrl::SetPos(Vector3 pos)
{
	m_frame->GetTransform().position = pos;
	m_LifeGauge->GetTransform().position = pos;
}

void GaugeCtrl::SetSize(Vector3 size)
{
	m_size = size;
}

void GaugeCtrl::SetTarget(Transform* trans)
{
	m_target = trans;
}

void GaugeCtrl::SetOffset(Vector3 offset)
{
	m_offset = offset;
}

LifeGaugeShaderInfo* GaugeCtrl::GetLifeShader()
{
	return m_LifeGauge->GetComponent<LifeGaugeShaderInfo>();
}

DefaultShaderInfo* GaugeCtrl::GetBackShader()
{
	return m_frame->GetComponent<DefaultShaderInfo>();
}

// EOF