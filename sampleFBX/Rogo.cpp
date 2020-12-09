#include "Rogo.h"
#include "DefaultShaderInfo.h"
#include "TextureData.h"
#include "UIMesh.h"

void Rogo::Awake()
{
	m_shader = AddComponent<DefaultShaderInfo>();
	m_shader->SetTexture(TEXTURE_ROGO);
	m_mesh = AddComponent<UIMesh>()->ChangeSize(496, 126, 1)->ChangePos(0, 60, 0);
	m_mesh->SetShader(*m_shader);
}

// EOF