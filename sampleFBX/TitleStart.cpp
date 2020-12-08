/**
 * @file TitleStart
 * @brief タイトルのスタートボタン
 */
#include "TitleStart.h"
#include "UIMesh.h"
#include "TextureData.h"
#include "DefaultShaderInfo.h"

static DefaultShaderInfo* m_shader;

void TitleStart::Awake()
{
	m_color = Vector3(0,0,0);
	m_add = 0.01f;
	m_alpha = 1;
	m_shader = AddComponent<DefaultShaderInfo>();
	m_shader->SetTexture(TEXTURE_PRESSENTER);
	m_mesh = AddComponent<UIMesh>()->ChangeSize(180, 100, 1)->ChangePos(0, -200, 0);
	m_mesh->SetShader(*m_shader);
}

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
	//m_alpha += m_add;
	m_shader->ChangeColor(m_color.x, m_color.y, m_color.z, m_alpha);
}

// EOF