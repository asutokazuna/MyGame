#include "GaugeCtrl.h"
#include "GameObject.h"
#include "LifeGauge.h"
#include "LifeGaugeShaderInfo.h"
#include "DefaultShaderInfo.h"

/**
 * @brief ‰Šú‰»ˆ—
 * @return ‚È‚µ
 */
void GaugeCtrl::Awake()
{
	m_frame = m_Parent->GetChild("frame");
	m_LifeGauge = m_Parent->GetChild<LifeGauge>();
	m_target = nullptr;
	m_offset = Vector3();
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
}

void GaugeCtrl::SetPos(Vector3 pos)
{
	m_frame->GetTransform().position = pos;
	m_LifeGauge->GetTransform().position = pos;
}

void GaugeCtrl::SetSize(Vector3 size)
{
	m_frame->GetTransform().scale = size;
	m_LifeGauge->GetTransform().scale = size;
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