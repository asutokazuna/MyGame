/**
 * @file TitleStart
 * @brief タイトルのスタートボタン
 */
#include "TitleStart.h"
#include "UIMesh.h"
#include "TextureData.h"
#include "DefaultShaderInfo.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void TitleStart::Awake()
{
	m_add = 0.01f;
	m_alpha = 1;
	m_shader = AddComponent<DefaultShaderInfo>();
	m_shader->SetTexture(TEXTURE_PRESSENTER);
	m_mesh = AddComponent<UIMesh>()->ChangeSize(420, 76, 1)->ChangePos(0, -200, 0);
	m_mesh->SetShader(*m_shader);
	m_shader->ChangeColor(0, 0, 0);
}

/**
 * @brief 更新処理
 * @return なし
 */
void TitleStart::Update()
{
	if (m_alpha >= 1) {
		m_alpha = 1;
		m_add *= -1;
	}
	else if(m_alpha <= 0){
		m_alpha = 0;
		m_add *= -1;
	}
	m_alpha += m_add;
	m_shader->ChangeColor(0, 0, 0, m_alpha);	// 黒色にする
}

// EOF