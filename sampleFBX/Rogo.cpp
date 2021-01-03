#include "Rogo.h"
#include "DefaultShaderInfo.h"
#include "TextureData.h"
#include "UIMesh.h"
#include "ExplosionShaderInfo.h"

#define ROGO_WIDTH (723 * 1.2f)		//!< ロゴの横幅
#define ROGO_HEIGHT (210 * 1.2f)		//!< ロゴの縦幅

static ExplosionShaderInfo* g_shader;

/**
 * @brief 初期化処理
 * @return なし
 */
void Rogo::Awake()
{
	m_shader = AddComponent<DefaultShaderInfo>();
	m_shader->SetTexture(TEXTURE_ROGO);
	g_shader = AddComponent<ExplosionShaderInfo>();
	g_shader->SetTexture(TEXTURE_ROGO_BLACK);
//	g_shader->SetNoizeTexture(TEXTURE_NOIZE);
	m_mesh = AddComponent<UIMesh>()->ChangeSize(ROGO_WIDTH, ROGO_HEIGHT , 1)->ChangePos(0, 100.0f, 0);
	m_mesh->SetPrimitive(6);
	m_mesh->SetShader(*g_shader);
}

void Rogo::InitParam()
{
	g_shader->SetFloat("Power", 0);
	g_shader->SetFloat("Fade", 0);
}

void Rogo::Move(float t)
{
	g_shader->SetFloat("Power", t);
}

void Rogo::Fade(float t)
{
	g_shader->SetFloat("Fade", t);
}

// EOF