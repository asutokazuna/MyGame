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

#define	TEXTURE_PressSpace	L"data/texture/Press_Space.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_WIN			L"data/texture/win.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_LOSE		L"data/texture/Lose.png"	// 読み込むテクスチャファイル名

HRESULT SceneResult::Init()
{
	m_Press = new GameObject();
	m_Press->AddComponent<UIMesh>()->ChangeSize(180, 100, 1)->ChangePos(0, -200, 0)->SetTexture(TEXTURE_PressSpace);
	m_Win = new GameObject();
	m_Win->AddComponent<UIMesh>()->ChangeSize(700, 400, 1)->ChangePos(0, 100, 0)->SetTexture(TEXTURE_WIN)->ChangeColor(1, 1, 0);
	m_Lose = new GameObject();
	m_Lose->AddComponent<UIMesh>()->ChangeSize(700, 400, 1)->ChangePos(0, 100, 0)->SetTexture(TEXTURE_LOSE);

	return E_NOTIMPL;
}

void SceneResult::Uninit()
{
	m_Press->Uninit();
	delete m_Press;
	m_Win->Uninit();
	delete m_Win;
	m_Lose->Uninit();
	delete m_Lose;
}

void SceneResult::Update()
{
	if (CInput::GetKeyTrigger(VK_SPACE)) {
		SceneManager::Change(SceneManager::SCENE_TITLE);
	}
	m_Press->Update();
	m_Win->Update();
	m_Lose->Update();
}

void SceneResult::Draw()
{
	m_Press->Draw();
	if (SceneGame::m_isVictory == true) {
		m_Win->Draw();
	}
	else {
		m_Lose->Draw();
	}
}

// EOF