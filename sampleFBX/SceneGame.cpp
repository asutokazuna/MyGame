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

bool SceneGame::m_isGameOver = false;
bool SceneGame::m_isVictory = true;

HRESULT SceneGame::Init()
{
	m_isGameOver = false;

	m_pCTPCamera = new CTPCamera();
	m_BCamera = new CBulletTime();
	CCamera::Set(m_pCTPCamera);
	//CCamera::Set(m_BCamera);

	m_pPlayer = new CPlayer();
	SetObj(m_pPlayer);
	m_pEnemy = new Enemy();
	SetObj(m_pEnemy);
	m_Field = new Field();
	SetObj(m_Field);
	m_Tower = new TowerManager();
	SetObj(m_Tower);
	m_Core = new CorePlayer();
	SetObj(m_Core);
	m_CoreEnemy = new CoreEnemy();
	SetObj(m_CoreEnemy);

	m_pCTPCamera->SetTransform(m_pPlayer->GetTransform());
	m_BCamera->Init();

	CScene::Init();
	m_pCTPCamera->Init();

	return S_OK;
}

void SceneGame::Uninit()
{
	m_BCamera->Uninit();
	CScene::Uninit();
	m_pCTPCamera->Uninit();

	delete m_CoreEnemy;
	delete m_Core;
	delete m_Tower;
	delete m_Field;
	delete m_BCamera;
	delete m_pEnemy;
	delete m_pPlayer;
	delete m_pCTPCamera;
}

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