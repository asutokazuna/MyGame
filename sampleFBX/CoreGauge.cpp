/**
 * @file CorePlayerGauge
 * @brief コアの残りHP表示コンポーネント
 */
#include "CoreGauge.h"
#include "GameObject.h"
#include "LifeGaugeShaderInfo.h"
#include "UIMesh.h"
#include "CoreState.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void CoreGauge::Awake()
{
	m_mesh = m_Parent->GetComponent<UIMesh>();
	m_shader = m_Parent->GetComponent<LifeGaugeShaderInfo>();
}

/**
 * @brief 更新処理
 * @return なし
 */
void CoreGauge::Update()
{
	if (m_state != nullptr &&
		m_shader != nullptr) {
		m_shader->SetFloat("Life", m_state->GetPercent());
	}
}

// EOF