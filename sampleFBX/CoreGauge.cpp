/**
 * @file CorePlayerGauge
 * @brief �R�A�̎c��HP�\���R���|�[�l���g
 */
#include "CoreGauge.h"
#include "GameObject.h"
#include "LifeGaugeShaderInfo.h"
#include "UIMesh.h"
#include "CoreState.h"

/**
 * @brief ����������
 * @return �Ȃ�
 */
void CoreGauge::Awake()
{
	m_mesh = m_Parent->GetComponent<UIMesh>();
	m_shader = m_Parent->GetComponent<LifeGaugeShaderInfo>();
}

/**
 * @brief �X�V����
 * @return �Ȃ�
 */
void CoreGauge::Update()
{
	if (m_state != nullptr &&
		m_shader != nullptr) {
		m_shader->SetFloat("Life", m_state->GetPercent());
	}
}

// EOF