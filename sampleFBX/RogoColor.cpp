/**
 * @file RogoColor
 * @brief 色付きのタイトルロゴオブジェクト
 */
#include "DefaultShaderInfo.h"
#include "TextureData.h"
#include "UIMesh.h"
#include "RogoColor.h"

#define ROGO_WIDTH (723* 1.2f)		//!< ロゴの横幅
#define ROGO_HEIGHT (210* 1.2f)		//!< ロゴの縦幅

/**
 * @brief 初期化処理
 * @return なし
 */
void RogoColor::Awake()
{
	m_shader = AddComponent<DefaultShaderInfo>();
	m_shader->SetTexture(TEXTURE_ROGO);
	m_mesh = AddComponent<UIMesh>()->ChangeSize(ROGO_WIDTH, ROGO_HEIGHT, 1)->ChangePos(0, 100.0f, 1);
	m_mesh->SetShader(*m_shader);
}

// EOF