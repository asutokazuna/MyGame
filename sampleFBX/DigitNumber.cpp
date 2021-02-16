/**
 * @file DigitNumber
 * @brief 数字表示
 * @author Ariga
 */
#include "DigitNumber.h"
#include "UIMesh.h"
#include "DefaultShaderInfo.h"
#include "TextureData.h"
#include "NumberDrawer.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void DigitNumber::Awake()
{
	m_mesh = AddComponent<UIMesh>()->ChangeSize(35,50,0);
	m_shader = AddComponent<DefaultShaderInfo>()->SetTexture(TEXTURE_NUMBER);
	AddComponent<NumberDrawer>();

	m_mesh->SetShader(*m_shader);
}

// EOF