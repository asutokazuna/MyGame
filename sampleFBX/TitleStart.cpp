/**
 * @file TitleStart
 * @brief タイトルのスタートボタン
 */
#include "TitleStart.h"
#include "UIMesh.h"
#include "TextureData.h"

void TitleStart::Awake()
{
	m_color = Vector3(1,1,1);
	m_add = 0.01f;
	m_alpha = 1;
	m_mesh = AddComponent<UIMesh>()->ChangeSize(180, 100, 1)->ChangePos(0, -200, 0)->SetTexture(TextureData::GetData(TEXTURE_PRESSENTER));
	SetActive(false);
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
	m_alpha += m_add;
	m_mesh->ChangeColor(m_color.x, m_color.y, m_color.z, m_alpha);
}

// EOF