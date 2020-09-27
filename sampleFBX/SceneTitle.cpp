/**
 * @file SceneTitle
 * @brief タイトルシーンクラス
 */
#include "SceneTitle.h"
#include "TitleUI.h"
#include "input.h"
#include "SceneManager.h"
#include "ObjectManager.h"

HRESULT SceneTitle::Init()
{
	m_UI = new TitleUI();
	SetObj(m_UI);

	CScene::Init();

	std::string test("test");

	GameObject* aaa = ObjectManager::Create<GameObject>(test);

	GameObject* temp = ObjectManager::FindObject<GameObject>(test);

	return E_NOTIMPL;
}

void SceneTitle::Uninit()
{
	CScene::Uninit();
	delete m_UI;
}

void SceneTitle::Update()
{
	if (CInput::GetKeyTrigger(VK_SPACE)) {
		SceneManager::Change(SceneManager::ESCENE::SCENE_GAME);
		return;
	}
	CScene::Update();
}

// EOF