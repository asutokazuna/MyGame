/**
 * @file StarParticle
 * @brief 星のエフェクト
 */
#include "StarParticle.h"
#include "UIMesh.h"
#include "DefaultShaderInfo.h"
#include "StarMove.h"
#include "TextureData.h"
#include "Graphics.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void StarParticle::Awake()
{
	
	m_shader = AddComponent<DefaultShaderInfo>()->SetTexture(TEXTURE_STAR);
	m_shader->ChangeAlpha(0.5f);
	m_mesh = AddComponent<UIMesh>()->ChangeSize(200, 200, 0)->ChangePos(0, -250, 0);
	m_mesh->SetBlendState(BS_ADDITIVE);
	m_mesh->SetShader(*m_shader);
	m_mesh->SetZwrite(false);

	m_backshader = AddComponent<DefaultShaderInfo>()->SetTexture(TEXTURE_EFFECT);
	m_backmesh = AddComponent<UIMesh>()->ChangeSize(200, 200, 0)->ChangePos(0, -250, 0);
	m_backmesh->SetBlendState(BS_ADDITIVE);
	m_backmesh->SetShader(*m_backshader);
	m_backmesh->SetZwrite(false);

	AddComponent<StarMove>()->SetBackShader(m_backshader);
}

// EOF