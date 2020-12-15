#include "DefaultShaderInfo.h"
#include "TextureData.h"
#include "UIMesh.h"
#include "RogoColor.h"

#define ROGO_WIDTH (723)
#define ROGO_HEIGHT (210)

void RogoColor::Awake()
{
	m_shader = AddComponent<DefaultShaderInfo>();
	m_shader->SetTexture(TEXTURE_ROGO);
	m_mesh = AddComponent<UIMesh>()->ChangeSize(ROGO_WIDTH, ROGO_HEIGHT, 1)->ChangePos(0, 100, 1);
	m_mesh->SetShader(*m_shader);
}

// EOF