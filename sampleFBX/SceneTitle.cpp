/**
 * @file SceneTitle
 * @brief タイトルシーンクラス
 */
#include "SceneTitle.h"
#include "TitleUI.h"
#include "input.h"
#include "SceneManager.h"
#include "ObjectManager.h"

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT SceneTitle::Init()
{
	m_UI = ObjectManager::Create<TitleUI>("TitleUI");

	return E_NOTIMPL;
}

/**
 * @brief 更新処理
 * @return  なし
 */
void SceneTitle::Update()
{
	if (CInput::GetKeyTrigger(VK_SPACE)) {
		SceneManager::Change(SceneManager::ESCENE::SCENE_GAME);
		return;
	}
}

// EOF