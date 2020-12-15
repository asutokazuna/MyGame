/**
 * @file SceneTitle
 * @brief タイトルシーンクラス
 */
#include "SceneTitle.h"
#include "input.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "TitleStateMachine.h"
#include "GameObject.h"
#include "TitleRogo.h"
#include "TitleStart.h"
#include "StarParticle.h"
#include "StarCreater.h"
#include "Rogo.h"
#include "DotsBG.h"
#include "TitleCamera.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void SceneTitle::Awake()
{
	m_camera = ObjectManager::Create<TitleCamera>("TitleCamera");
	ObjectManager::Create<TitleRogo>("TitleRogo");
	ObjectManager::Create<TitleStart>("TitleStart");
	ObjectManager::Create<GameObject>("StarManager")->AddComponent<StarCreater>();
	ObjectManager::Create<Rogo>("Rogo");
	//ObjectManager::Create<DotsBG>("DotsBG");

	m_stateMachine = ObjectManager::Create<GameObject>("StateMachine");
	m_stateMachine->AddComponent<TitleStateMachine>();
	CCamera::Set(m_camera);
}

/**
 * @brief 更新処理
 * @return  なし
 */
void SceneTitle::Update()
{
	m_stateMachine->GetComponent<TitleStateMachine>()->GetState();
	if (CInput::GetKeyTrigger(VK_SPACE)) {
		SceneManager::Change(SceneManager::ESCENE::SCENE_GAME);
		return;
	}
}

// EOF