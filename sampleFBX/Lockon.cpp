/**
 * @file Lockon
 */
#include "Lockon.h"
#include "UIMesh.h"
#include "TextureData.h"
#include "DefaultShaderInfo.h"

#define SIZE (40)

void Lockon::Awake()
{
	Mesh* mesh =AddComponent<UIMesh>()->ChangeSize(SIZE, SIZE,1);
	ShaderInfo* shader = AddComponent<DefaultShaderInfo>()->SetTexture(TEXTURE_LOCKON)->ChangeColor(1,1,0);
	mesh->SetShader(*shader);
}

// EOF