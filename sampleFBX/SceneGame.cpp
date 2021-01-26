/**
 * @file SceneGame
 * @brief ゲームシーンクラス
 */
#include "SceneGame.h"
#include "CPlayer.h"
#include "Enemy.h"
#include "CTPCamera.h"
#include "BulletTime.h"
#include "Field.h"
#include "TowerManager.h"
#include "CorePlayer.h"
#include "CoreEnemy.h"
#include "SceneManager.h"
#include "input.h"
#include "ObjectManager.h"
#include "RangeCursor.h"
#include "CoreGaugeUI.h"
#include "CharacterSpawner.h"
#include "GameCameraManager.h"

bool SceneGame::m_isGameOver = false;
bool SceneGame::m_isVictory = true;

/**
 * @brief 初期化処理
 * @return なし
 */
void SceneGame::Awake()
{
	ObjectManager::Create<GameCameraManager>("GameCameraManager");
	ObjectManager::Create<CharacterSpawner>("CharacterSpawner");
	m_pPlayer	= ObjectManager::Create<CPlayer>("Player");
	ObjectManager::Create<RangeCursor>("RangeCursor");
	m_pEnemy	= ObjectManager::Create<Enemy>("Enemy");
	m_Field		= ObjectManager::Create<Field>("Field");
	m_Tower		= ObjectManager::Create<TowerManager>("TowerManager");
	m_Core		= ObjectManager::Create<CorePlayer>("CorePlayer");
	m_CoreEnemy = ObjectManager::Create<CoreEnemy>("CoreEnemy");
	ObjectManager::Create<CoreGaugeUI>("CoreGaugeUI");
	m_pCTPCamera = ObjectManager::Create<CTPCamera>("CTPCamera");
}

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT SceneGame::Init()
{
	m_isGameOver = false;

	return S_OK;
}

/**
 * @brief 終了処理
 * @return なし
 */
void SceneGame::Uninit()
{
	CScene::Uninit();

}

/**
 * @brief 更新処理
 * @return  なし
 */
void SceneGame::Update()
{
	if (m_Core->GetLife() <= 0 ) {
		m_isGameOver = true;
		m_isVictory = false;
	}
	else if (m_CoreEnemy->GetLife() <= 0) {
		m_isGameOver = true;
		m_isVictory = true;
	}

	if (m_isGameOver == true) {
		SceneManager::Change(SceneManager::SCENE_RESULT);
	}
#ifdef _DEBUG
	if(CInput::GetKeyTrigger(VK_0))
	SceneManager::Change(SceneManager::SCENE_RESULT);
#endif

	CScene::Update();
}

void SceneGame::GameOver()
{
	m_isGameOver = true;
}

// EOF