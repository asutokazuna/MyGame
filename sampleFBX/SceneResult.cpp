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

#define	TEXTURE_PressSpace	L"data/texture/Press_Space.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_WIN			L"data/texture/win.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_LOSE		L"data/texture/Lose.png"	// 読み込むテクスチャファイル名

/**
 * @brief 初期化処理
 * @return  なし
 */
HRESULT SceneResult::Init()
{
	m_Press = ObjectManager::Create<GameObject>("Press");
	m_Press->AddComponent<UIMesh>()->ChangeSize(180, 100, 1)->ChangePos(0, -200, 0)->SetTexture(TEXTURE_PressSpace);
	if (SceneGame::m_isVictory == true) {
		m_Win = ObjectManager::Create<GameObject>("Win");
		m_Win->AddComponent<UIMesh>()->ChangeSize(700, 400, 1)->ChangePos(0, 100, 0)->SetTexture(TEXTURE_WIN)->ChangeColor(1, 1, 0);
	}
	else {
		m_Lose = ObjectManager::Create<GameObject>("Lose");
		m_Lose->AddComponent<UIMesh>()->ChangeSize(700, 400, 1)->ChangePos(0, 100, 0)->SetTexture(TEXTURE_LOSE);
	}
	return E_NOTIMPL;
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