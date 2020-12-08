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

void StarParticle::Awake()
{
	
	m_shader = AddComponent<DefaultShaderInfo>()->SetTexture(TEXTURE_STAR);
	m_mesh = AddComponent<UIMesh>()->ChangeSize(200, 200, 0)->ChangePos(0, -250, 0);
	m_mesh->SetBlendState(BS_ALPHABLEND);
	m_mesh->SetShader(*m_shader);

	m_backshader = AddComponent<DefaultShaderInfo>()->SetTexture(TEXTURE_EFFECT);
	m_backmesh = AddComponent<UIMesh>()->ChangeSize(200, 200, 0)->ChangePos(0, -250, 0);
	m_backmesh->SetBlendState(BS_ADDITIVE);
	m_backmesh->SetShader(*m_backshader);

	AddComponent<StarMove>()->SetBackShader(m_backshader);
}

// EOF