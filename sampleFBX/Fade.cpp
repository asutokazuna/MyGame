/**
 * @file Fade
 * @brief フェードクラス
 */
#include "Fade.h"
#include "UIMesh.h"
#include "main.h"
#include "GameObject.h"
#include "ImGui/imgui.h"

Fade* Fade::m_instance = nullptr;
static Mesh* UI;

void Fade::InitInst()
{
	m_Mesh = new GameObject();

	m_Mesh->Init();
	UI = m_Mesh->AddComponent<UIMesh>()->ChangeSize(SCREEN_WIDTH, SCREEN_HEIGHT, 1)->ChangeColor(0, 0, 0, 1)
		->ChangePos(0,0,-1);

	m_Alpha = 0.0f;
	m_isFade = false;
	m_State = FADE_NONE;
}

void Fade::UninitInst()
{
	delete m_Mesh;
}

void Fade::UpdateInst()
{
	if (m_State == FADE_NONE) {
		return;
	}
	if (m_State == FADE_IN)
	{
		if (m_Alpha > 0){
			m_Alpha -= 0.01f;
		}
		else {
			m_Alpha = 0.0f;
			m_State = FADE_NONE;
			m_isFade = false;
		}
	}
	else if(m_State == FADE_OUT)
	{
		if (m_Alpha < 1) {
			m_Alpha += 0.01f;
		}
		else {
			m_Alpha = 1.0f;
			m_State = FADE_NONE;
			m_isFade = false;
		}
	}
}

void Fade::DrawInst()
{
#ifdef _DEBUG
	ImGui::Begin("Fade");
	ImGui::SliderFloat("FadeAlpha", &m_Alpha, 0, 1);
	ImGui::RadioButton("FADE_NONE", &m_State, 0);
	ImGui::RadioButton("FADE_IN", &m_State, 1);
	ImGui::RadioButton("FADE_OUT", &m_State, 2);
	ImGui::End();
#endif // _DEBUG

	UI->ChangeColor(0,0,0, m_Alpha);

	m_Mesh->Draw();
}

bool Fade::IsFadeInst()
{
	return m_isFade;
}

void Fade::SetState(FADE_STATE state)
{
	m_State = state;
	if (state == FADE_IN) {
		m_Alpha = 1;
		m_isFade = true;
	}
	else if (state == FADE_OUT) {
		m_Alpha = 0;
		m_isFade = true;
	}
}

void Fade::Init()
{
	Get()->InitInst();
}

void Fade::Uninit()
{
	Get()->UninitInst();
	delete m_instance;
}

void Fade::Update()
{
	Get()->UpdateInst();
}

void Fade::Draw()
{
	Get()->DrawInst();
}

bool Fade::IsFade()
{
	return Get()->IsFadeInst();
}

void Fade::FadeIn()
{
	Get()->SetState(FADE_IN);
}

void Fade::FadeOut()
{
	Get()->SetState(FADE_OUT);
}

Fade* Fade::Get()
{
	if (m_instance == nullptr) {
		m_instance = new Fade();
	}

	return m_instance;
}

// EOF