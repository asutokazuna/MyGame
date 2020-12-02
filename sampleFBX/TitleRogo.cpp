/**
 * @file TitleRogo
 * @brief タイトルロゴ
 */
#include "TitleRogo.h"
#include "UIMesh.h"
#include "TextureData.h"
#include "DefaultShaderInfo.h"
static DefaultShaderInfo* m_shader;
/**
 * @brief 初期化処理
 * @return なし
 */
void TitleRogo::Awake()
{
	m_shader = AddComponent<DefaultShaderInfo>();
	m_shader->SetTexture(TEXTURE_TITLE_ROGO);
	m_mesh = AddComponent<UIMesh>()->ChangeSize(700, 400, 1)->ChangePos(0, 100, 0);// ->SetTexture(TextureData::GetData(TEXTURE_TITLE_ROGO));
	m_mesh->SetShader(*m_shader);
}

// EOF