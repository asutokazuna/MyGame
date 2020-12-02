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

/**
 * @brief 初期化処理
 * @return  なし
 */
void SceneResult::Awake()
{
	m_Press = ObjectManager::Create<GameObject>("Press");
	m_Press->AddComponent<UIMesh>()->ChangeSize(180, 100, 1)->ChangePos(0, -200, 0);// ->SetTexture(TextureData::GetData(TEXTURE_PRESSENTER));
	if (SceneGame::m_isVictory == true) {
		m_Win = ObjectManager::Create<GameObject>("Win");
		m_Win->AddComponent<UIMesh>()->ChangeSize(700, 400, 1)->ChangePos(0, 100, 0);// ->SetTexture(TextureData::GetData(TEXTURE_WIN))->ChangeColor(1, 1, 0);
	}
	else {
		m_Lose = ObjectManager::Create<GameObject>("Lose");
		m_Lose->AddComponent<UIMesh>()->ChangeSize(700, 400, 1)->ChangePos(0, 100, 0);// ->SetTexture(TextureData::GetData(TEXTURE_LOSE));
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

// EOF