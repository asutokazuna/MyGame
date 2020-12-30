/**
 * @file GaugeUI
 * @brief UI用ゲージ表示オブジェクト
 */
#include "GaugeUI.h"
#include "UIMesh.h"
#include "LifeGaugeShaderInfo.h"

/**
 * @breif 初期化処理
 * @return なし
 */
void GaugeUI::Awake()
{
	Mesh* mesh = AddComponent<UIMesh>();
	ShaderInfo* shader = AddComponent<LifeGaugeShaderInfo>();
	mesh->SetShader(*shader);
}

// EOF