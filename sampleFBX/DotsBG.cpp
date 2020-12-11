/**
 * @file DotsBG
 * @brief 水玉模様のオブジェクト
 */
#include "DotsBG.h"
#include "UIMesh.h"
#include "DefaultShaderInfo.h"
#include "TextureData.h"
#include "DotsBGMove.h"

/**
 * @brief 初期化
 * @retrun なし
 */
void DotsBG::Awake()
{
	m_mesh = AddComponent<UIMesh>();
	m_mesh->ChangePos(0, -SCREEN_CENTER_Y, 0)->ChangeSize(SCREEN_WIDTH, SCREEN_CENTER_Y / 2, 1)
		->SetBlendState(BS_SUBTRACTION);
	m_shader = AddComponent<DefaultShaderInfo>()->SetTexture(TEXTURE_POLKADOTS);
	m_shader->ChangeAlpha(0.1f);
	m_mesh->SetShader(*m_shader);
	AddComponent<DotsBGMove>()->SetShader(m_shader);
}

// EOF