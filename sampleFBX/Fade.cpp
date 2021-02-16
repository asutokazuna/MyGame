/**
 * @file Fade
 * @brief フェードクラス
 * @author Ariga
 */
#include "Fade.h"
#include "UIMesh.h"
#include "main.h"
#include "GameObject.h"
#include "ImGui/imgui.h"
#include "DefaultShaderInfo.h"


/**
 * @brief 初期化
 * @return なし
 */
void Fade::InitInst()
{
	m_Mesh = new GameObject();

	static Mesh* UI;
	UI = m_Mesh->AddComponent<UIMesh>()->ChangeSize(SCREEN_WIDTH, SCREEN_HEIGHT, 1)
		->ChangePos(0,0,-1);
	m_shader = m_Mesh->AddComponent<DefaultShaderInfo>()->ChangeColor(0, 0, 0, 1);
	UI->SetShader(*m_shader);
	m_Mesh->Init();
	m_Alpha = 0.0f;
	m_isFade = false;
	m_State = FADE_NONE;
}

/**
 * @brief 終了
 * @return なし
 */
void Fade::UninitInst()
{
	m_Mesh->Uninit();
	delete m_Mesh;
}

/**
 * @brief 更新
 * @return なし
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
	m_Mesh->Update();
}

/**
 * @brief 描画
 * @return なし
 */
void Fade::DrawInst()
{
#ifdef _DEBUG
	if (ImGui::TreeNode("Fade")) {
		ImGui::SliderFloat("FadeAlpha", &m_Alpha, 0, 1);
		ImGui::RadioButton("FADE_NONE", &m_State, 0);
		ImGui::RadioButton("FADE_IN", &m_State, 1);
		ImGui::RadioButton("FADE_OUT", &m_State, 2);
		ImGui::TreePop();
	}
#endif // _DEBUG

	m_shader->ChangeColor(0,0,0, m_Alpha);

	m_Mesh->Draw();
}

/**
 * @brief フェード中か判定する
 * @return フェード中ならtrue
 */
bool Fade::IsFadeInst()
{
	return m_isFade;
}

/**
 * @brief フェード処理
 * @return なし
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
 * @brief 初期化
 * @return なし
 */
void Fade::Init()
{
	GetInstance().InitInst();
}

/**
 * @brief 終了
 * @return なし
 */
void Fade::Uninit()
{
	GetInstance().UninitInst();
}

/**
 * @brief 更新
 * @return なし
 */
void Fade::Update()
{
	GetInstance().UpdateInst();
}

/**
 * @brief 描画
 * @return なし
 */
void Fade::Draw()
{
	GetInstance().DrawInst();
}

/**
 * @brief フェード中か判定する
 * @return フェード中ならtrue
 */
bool Fade::IsFade()
{
	return GetInstance().IsFadeInst();
}

/**
 * @brief フェードイン
 * @return なし
 */
void Fade::FadeIn()
{
	GetInstance().SetState(FADE_IN);
}

/**
 * @brief フェードアウト
 * @return なし
 */
void Fade::FadeOut()
{
	GetInstance().SetState(FADE_OUT);
}

// EOF