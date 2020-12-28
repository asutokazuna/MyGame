#include "DigitNumber.h"
#include "UIMesh.h"
#include "DefaultShaderInfo.h"
#include "TextureData.h"
#include "NumberDrawer.h"

/**
 * @brief ‰Šú‰»ˆ—
 * @return ‚È‚µ
 */
void DigitNumber::Awake()
{
	AddComponent<NumberDrawer>();
	m_mesh = AddComponent<UIMesh>()->ChangeSize(35,50,0);
	m_shader = AddComponent<DefaultShaderInfo>()->SetTexture(TEXTURE_NUMBER);

	m_mesh->SetShader(*m_shader);
}

// EOF