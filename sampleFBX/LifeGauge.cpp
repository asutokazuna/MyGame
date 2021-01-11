/**
 * @brief ゲージに使う手前部分（背景無し）ビルボード
 */
#include "LifeGauge.h"
#include "Billboard.h"
#include "LifeGaugeShaderInfo.h"

void LifeGauge::Awake()
{
	Mesh* mesh = AddComponent<Billboard>();
	ShaderInfo* shader = AddComponent<LifeGaugeShaderInfo>();
	mesh->SetShader(*shader);
}

// EOF