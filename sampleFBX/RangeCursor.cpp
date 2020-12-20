/**
 * @file RangeCursor
 * @brief UŒ‚”ÍˆÍ‚ÌUI•\¦
 */
#include "RangeCursor.h"
#include "UIMesh.h"
#include "DefaultShaderInfo.h"
#include "TextureData.h"

void RangeCursor::Awake()
{
	Mesh* mesh = AddComponent<UIMesh>()->ChangeSize(200,200,0);
	ShaderInfo* m_shader = AddComponent<DefaultShaderInfo>()->SetTexture(TEXTURE_CURSOR)->ChangeAlpha(0.5f);
	mesh->SetShader(*m_shader);
}

// EOF