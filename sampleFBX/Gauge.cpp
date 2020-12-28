/**
 * @file Gauge
 * @brief ゲージ表示クラス
 */
#include "Gauge.h"
#include "Billboard.h"
#include "LifeGauge.h"
#include "LifeGaugeShaderInfo.h"
#include "GaugeCtrl.h"

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
	m_LifeGauge = new LifeGauge();
	m_frame = new GameObject();
	m_frame->SetName("frame");
	SetChild(m_LifeGauge);
	SetChild(m_frame);
	AddComponent<GaugeCtrl>()->SetSize(Vector3(50, 30, 1));
	m_frame->AddComponent<Billboard>()->ChangeColor(1, 1, 1);
	m_LifeGauge->GetComponent<LifeGaugeShaderInfo>()->ChangeColor(1, 0.5f, 0);
}

// EOF