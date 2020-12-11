#include "Rogo.h"
#include "DefaultShaderInfo.h"
#include "TextureData.h"
#include "UIMesh.h"

#define ROGO_WIDTH (496)
#define ROGO_HEIGHT (126)

static float num = 1;

void Rogo::Awake()
{
	m_shader = AddComponent<DefaultShaderInfo>();
	m_shader->SetTexture(TEXTURE_ROGO);
	m_mesh = AddComponent<UIMesh>()->ChangeSize(ROGO_WIDTH * 1.6f, ROGO_HEIGHT * 1.6f, 1)->ChangePos(0, 100, 0);
	m_mesh->SetShader(*m_shader);
}

// EOF