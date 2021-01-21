/**
 * @file GameCameraManager .cpp
 * @brief ゲームシーンのカメラ管理オブジェクト
 */
#include "GameCameraManager.h"
#include "CameraStateMachine.h"
#include "CCamera.h"
#include "CTPCamera.h"
#include "DeadCamera.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void GameCameraManager::Awake()
{
	CTPCamera* TPCamera = new CTPCamera();
	TPCamera->SetName("TPCamera");
	SetChild(TPCamera);
	CCamera::Set(TPCamera);
	DeadCamera* m_deadCamera = new DeadCamera();
	m_deadCamera->SetName("DeadCamera");
	SetChild(m_deadCamera);
	CCamera::Set(m_deadCamera);
	m_deadCamera->SetActive(false);
	AddComponent<CameraStateMachine>();
}

/**
 * @brief 終了処理
 * @return なし
 */
void GameCameraManager::Uninit()
{
	GameObject::Uninit();
}

// EOF