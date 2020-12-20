#include "Number.h"
#include "UIMesh.h"
#include "DefaultShaderInfo.h"
#include "TextureData.h"
#include "NumberDrawer.h"

/**
 * @brief ����������
 * @return �Ȃ�
 */
void Number::Awake()
{
	AddComponent<NumberDrawer>();
	m_mesh = AddComponent<UIMesh>()->ChangeSize(200,200,0);
	m_shader = AddComponent<DefaultShaderInfo>()->SetTexture(TEXTURE_NUMBER);

	m_mesh->SetShader(*m_shader);
}

// EOF