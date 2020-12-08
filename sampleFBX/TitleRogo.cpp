/**
 * @file TitleRogo
 * @brief タイトルロゴ
 */
#include "TitleRogo.h"
#include "UIMesh.h"
#include "TextureData.h"
#include "ClothShaderInfo.h"

#define START_POS (-SCREEN_CENTER_X - 700)
#define END_POS (0)
#define MOVE_TIME (180)

/**
 * @brief 初期化処理
 * @return なし
 */
void TitleRogo::Awake()
{
	m_clothshader = AddComponent<ClothShaderInfo>();
	m_clothshader->SetTexture(TEXTURE_TITLE_ROGO);
	m_mesh = AddComponent<UIMesh>()->ChangeSize(SCREEN_WIDTH, SCREEN_HEIGHT, 1)->ChangePos(START_POS, 0, 0);
	m_mesh->SetPrimitive(6);
	m_mesh->SetBlendState(BS_SUBTRACTION);
	m_clothshader->ChangeAlpha(0.4f);
	m_mesh->SetShader(*m_clothshader);
	m_time = 0;
	m_power = 0.1f;
}

void TitleRogo::Move()
{
	float posX;

	posX = MyMath::Lerp(START_POS, END_POS, m_time / MOVE_TIME);

	if (posX > END_POS) {
		posX = END_POS;
	}
	m_mesh->ChangePos(posX, 0, 0);

	m_time++;
}

bool TitleRogo::IsArrive()
{
	if (m_time < MOVE_TIME) {
		return false;
	}

	m_mesh->ChangePos(END_POS, 0, 0);

	return true;
}

void TitleRogo::MovePower()
{
	if (m_power < 0.0001f) {
		return;
	}
	m_power -= 0.0005f;
	m_clothshader->SetFloat("Power", m_power);
}

void TitleRogo::InitParam()
{
	m_mesh->ChangePos(START_POS, 0, 0);
	m_time = 0;
	m_mesh->SetShader(*m_clothshader);
	m_mesh->SetPrimitive(6);
	m_power = 0.1f;
}

// EOF