/**
 * @file SceneResult
 * @brief リザルトシーンクラス
 */
#include "SceneResult.h"
#include "input.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "UIMesh.h"
#include "SceneGame.h"
#include "ObjectManager.h"
#include "TextureData.h"
#include "DefaultShaderInfo.h"

/**
 * @brief 初期化処理
 * @return  なし
 */
void SceneResult::Awake()
{
	ShaderInfo* pressShader;
	ShaderInfo* texShader;

	m_Press = ObjectManager::Create<GameObject>("Press");
	pressShader = m_Press->AddComponent< DefaultShaderInfo>()->SetTexture(TEXTURE_PRESSENTER);
	m_Press->AddComponent<UIMesh>()->ChangeSize(420, 76, 1)->ChangePos(0, -200, 0)->SetShader(*pressShader);// ->SetTexture(TextureData::GetData(TEXTURE_PRESSENTER));
	if (SceneGame::m_isVictory == true) {
		m_Win = ObjectManager::Create<GameObject>("Win");
		texShader = m_Win->AddComponent<DefaultShaderInfo>()->SetTexture(TEXTURE_WIN);
		m_Win->AddComponent<UIMesh>()->ChangeSize(162 * 4, 76 * 4, 1)->ChangePos(0, 100, 0)->SetShader(*texShader);// ->SetTexture(TextureData::GetData(TEXTURE_WIN))->ChangeColor(1, 1, 0);
	}
	else {
		m_Lose = ObjectManager::Create<GameObject>("Lose");
		texShader = m_Win->AddComponent<DefaultShaderInfo>()->SetTexture(TEXTURE_LOSE);
		m_Lose->AddComponent<UIMesh>()->ChangeSize(183 * 4, 76 * 4, 1)->ChangePos(0, 100, 0)->SetShader(*texShader);// ->SetTexture(TextureData::GetData(TEXTURE_LOSE));
	}
}

/**
 * @brief 更新処理
 * @return  なし
 */
void SceneResult::Update()
{
	if (CInput::GetKeyTrigger(VK_SPACE)) {
		SceneManager::Change(SceneManager::SCENE_TITLE);
	}
}

#ifdef _DEBUG

void SceneResult::Draw()
{
	CScene::Draw();

	if (ImGui::TreeNode("Result")) {
		float *pressPos[3] = { &m_Win->GetTransform().scale.x, &m_Win->GetTransform().scale.y , &m_Win->GetTransform().scale.z };
		ImGui::SliderFloat3("pressPos", *pressPos, -1000.0f, 500.0f);
		ImGui::TreePop();
	}
}

#endif

// EOF