/**
 * @file TitleRogo
 * @brief タイトルロゴ
 */
#include "TitleRogo.h"
#include "UIMesh.h"
#include "TextureData.h"
#include "ClothShaderInfo.h"
#include "ExplosionShaderInfo.h"

#define START_POS (-SCREEN_CENTER_X - 700 * 2)
#define MOVE_TIME (100)

/**
 * @brief 初期化処理
 * @return なし
 */
void TitleRogo::Awake()
{
	m_clothshader = AddComponent<ClothShaderInfo>();
	m_clothshader->SetTexture(TEXTURE_TITLE_ROGO);
	m_clothshader->SetNoizeTexture(TEXTURE_NOIZE);
	m_expShader = AddComponent<ExplosionShaderInfo>();
	m_expShader->SetTexture(TEXTURE_TITLE_ROGO);
	m_mesh = AddComponent<UIMesh>()->ChangeSize(SCREEN_WIDTH*1.6, SCREEN_HEIGHT*1.6, 1);// ->ChangePos(START_POS, 0, 0);
	m_mesh->SetPrimitive(6);
	//m_mesh->SetBlendState(BS_SUBTRACTION);
	//m_clothshader->ChangeAlpha(0.4f);
	m_mesh->SetShader(*m_clothshader);
	//m_mesh->SetShader(*m_expShader);
	m_time = 0;
	m_power = 0.1f;
	m_fadeValue = 0;
	m_endPos = 0;
}

bool TitleRogo::Move(float startPos, float endPosX, int time)
{
	float posX;

	m_endPos = endPosX;
	posX = MyMath::Lerp(startPos, endPosX, time / (float)MOVE_TIME);

	if (posX > m_endPos) {
		posX = m_endPos;
	}
	m_mesh->ChangePos(posX, 0, 0);

	m_time++;
	if (posX >= m_endPos) {
		return true;
	}
	else {
		return false;
	}
}

bool TitleRogo::IsArrive()
{
	if (m_time < MOVE_TIME) {
		return false;
	}

	m_mesh->ChangePos(m_endPos, 0, 0);

	return true;
}

bool TitleRogo::MovePower(float power)
{
	m_power += power;
	m_clothshader->SetFloat("Power", m_power);
	if (m_power < 0.0001f) {
		return true;
	}
	return false;
}

bool  TitleRogo::Fade(float speed)
{
	m_fadeValue += speed;
	m_clothshader->SetFloat("Fade", m_fadeValue);
	if (m_fadeValue >= 1) {
		return true;
	}
	return false;
}

bool  TitleRogo::FadeOUT(float speed)
{
	m_fadeValue -= speed;
	m_clothshader->SetFloat("Fade", m_fadeValue);
	if (m_fadeValue < 0) {
		return true;
	}
	return false;
}


void TitleRogo::InitParam()
{
	m_mesh->ChangePos(START_POS, 0, 0);
	m_time = 0;
	m_mesh->SetShader(*m_clothshader);
	m_mesh->SetPrimitive(6);
	m_power = 0.1f;
	m_fadeValue = 0;
	m_clothshader->SetFloat("Power", m_power);
	m_clothshader->SetFloat("Fade", m_fadeValue);
}

// EOF