/**
 * @file Fade
 * @brief �t�F�[�h�N���X
 */
#include "Fade.h"
#include "UIMesh.h"
#include "main.h"
#include "GameObject.h"
#include "ImGui/imgui.h"

static Mesh* UI;

/**
 * @brief ������
 * @return �Ȃ�
 */
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

/**
 * @brief �I��
 * @return �Ȃ�
 */
void Fade::UninitInst()
{
	delete m_Mesh;
}

/**
 * @brief �X�V
 * @return �Ȃ�
 */
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

/**
 * @brief �`��
 * @return �Ȃ�
 */
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

/**
 * @brief �t�F�[�h�������肷��
 * @return �t�F�[�h���Ȃ�true
 */
bool Fade::IsFadeInst()
{
	return m_isFade;
}

/**
 * @brief �t�F�[�h����
 * @return �Ȃ�
 */
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

/**
 * @brief ������
 * @return �Ȃ�
 */
void Fade::Init()
{
	GetInstance().InitInst();
}

/**
 * @brief �I��
 * @return �Ȃ�
 */
void Fade::Uninit()
{
	GetInstance().UninitInst();
}

/**
 * @brief �X�V
 * @return �Ȃ�
 */
void Fade::Update()
{
	GetInstance().UpdateInst();
}

/**
 * @brief �`��
 * @return �Ȃ�
 */
void Fade::Draw()
{
	GetInstance().DrawInst();
}

/**
 * @brief �t�F�[�h�������肷��
 * @return �t�F�[�h���Ȃ�true
 */
bool Fade::IsFade()
{
	return GetInstance().IsFadeInst();
}

/**
 * @brief �t�F�[�h�C��
 * @return �Ȃ�
 */
void Fade::FadeIn()
{
	GetInstance().SetState(FADE_IN);
}

/**
 * @brief �t�F�[�h�A�E�g
 * @return �Ȃ�
 */
void Fade::FadeOut()
{
	GetInstance().SetState(FADE_OUT);
}

// EOF