﻿/**
 * @file SceneTitle
 * @brief タイトルシーンクラス
 */
#include "SceneTitle.h"
#include "input.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "TitleStateMachine.h"
#include "GameObject.h"
#include "TitleStart.h"
#include "StarCreater.h"
#include "Rogo.h"
#include "TitleCamera.h"
#include "RogoColor.h"
#include "Sound.h"
#include "SoundData.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void SceneTitle::Awake()
{
	m_camera = ObjectManager::Create<TitleCamera>("TitleCamera");
	ObjectManager::Create<TitleStart>("TitleStart");
	ObjectManager::Create<RogoColor>("RogoColor");
	ObjectManager::Create<Rogo>("Rogo");
	ObjectManager::Create<GameObject>("StarManager")->AddComponent<StarCreater>();

	m_stateMachine = ObjectManager::Create<GameObject>("StateMachine");
	m_stateMachine->AddComponent<TitleStateMachine>();
	CCamera::Set(m_camera);
	CSound::Play(SOUND_LABEL_TITLE);
}

/**
 * @brief 更新処理
 * @return  なし
 */
void SceneTitle::Update()
{
	// 現在のステートの取得
	int state = m_stateMachine->GetComponent<TitleStateMachine>()->GetState();

	// スペースを押したとき
	if (CInput::GetKeyTrigger(VK_SPACE)) 
	{
		// 待機でなければ待機へ
		if (state != TITLE_STATE::E_TITLE_STATE_IDOL) {
			m_stateMachine->GetComponent<TitleStateMachine>()->GoToState(E_TITLE_STATE_IDOL);
		}
		else // 待機の時はシーン遷移
		{
			SceneManager::Change(SceneManager::ESCENE::SCENE_GAME);
			return;
		}
	}

	if (CSound::IsPlaying(SOUND_LABEL_TITLE) == false) {
		CSound::Play(SOUND_LABEL_TITLE);
	}
}

// EOF