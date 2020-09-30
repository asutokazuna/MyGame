/**
 * @file SceneManager
 * @brief シーンマネージャークラス
 */
#include "SceneManager.h"
#include "SceneGame.h"
#include "Scene.h"
#include "ModelData.h"
#include "Graphics.h"
#include "CTPCamera.h"
#include "ShaderData.h"
#include "Light.h"
#include "SceneTitle.h"
#include "Fade.h"
#include "Collision.h"
#include "SceneResult.h"
#include "CSky.h"
#include "CCamera.h"
#include "ObjectManager.h"
#include "TextureData.h"

CScene* SceneManager::m_nowScene = nullptr;
int SceneManager::m_SceneID = 0;
int SceneManager::m_NextSceneID = 0;

/**
 * @brief コンストラクタ
 */
SceneManager::SceneManager(): m_pCamera(nullptr),m_pSky(nullptr)
{
}

/**
 * @brief 初期化処理
 * @return なし
 */
void SceneManager::Init()
{
	ShaderData::Init();
	ModelData::Init();
	TextureData::Init();

	// 全オブジェクト初期化
	m_pCamera = new CCamera();
	CCamera::Set(m_pCamera);
	m_pCamera->Init();

	m_pSky = new CSky();
	m_pSky->Init();
	Fade::Init();

	m_nowScene = new SceneTitle();
	m_nowScene->Awake();
	ObjectManager::Awake();

	m_nowScene->Init();
	ObjectManager::Init();
}

/**
 * @brief 終了処理
 * @return なし
 */
void SceneManager::Uninit()
{
	ObjectManager::Uninit();

	if(m_nowScene)
	m_nowScene->Uninit();


	if(m_pSky)
	m_pSky->Uninit();
	if(m_pCamera)
	m_pCamera->Uninit();

	Fade::Uninit();
	ModelData::Uninit();
	ShaderData::Uninit();
	Light::Fin();
	
	delete m_pSky;
	delete m_pCamera;
	delete m_nowScene;
}

/**
 * @brief 更新処理
 * @return  なし
 */
void SceneManager::Update()
{
	Fade::Update();
	if (Fade::IsFade() == true) {
		return;
	}
	Change();

	if (Fade::IsFade() == true) {
		return;
	}

	ObjectManager::Update();
	m_nowScene->Update();
	CCamera::Get()->Update();

	Collision::Check();
}

/**
 * @brief 描画処理
 * @return  なし
 */
void SceneManager::Draw()
{	
	m_pSky->Draw();
	CCamera::Get()->Draw();
	m_nowScene->Draw();

	ObjectManager::Draw();
	Fade::Draw();
}

/**
 * @brief デフォルトのカメラを設定
 * @return なし
 */
void SceneManager::SetDefCamera()
{
	CCamera::Set(m_pCamera);
	m_pCamera->Init();
}

/**
 * @brief シーンチェンジ
 * @return なし
 */
void SceneManager::Change()
{
	if (m_SceneID == m_NextSceneID) {
		return;
	}

	m_SceneID = m_NextSceneID;

	ObjectManager::Uninit();
	m_nowScene->Uninit();
	delete m_nowScene;
	ObjectManager::Clear();

	switch (m_SceneID)
	{
	case SceneManager::SCENE_TITLE:
		m_nowScene = new SceneTitle();
		break;
	case SceneManager::SCENE_GAME:
		m_nowScene = new SceneGame();
		break;
	case SceneManager::SCENE_RESULT:
		m_nowScene = new SceneResult();
		break;
	default:
		m_nowScene = new SceneGame();
		break;
	}
	SetDefCamera();
	m_nowScene->Awake();
	ObjectManager::Awake();

	m_nowScene->Init();

	ObjectManager::Init();
	Fade::FadeIn();
}

/**
 * @brief シーンチェンジ
 * @param sceneID 移動先のシーンのID
 * @return なし
 */
void SceneManager::Change(ESCENE sceneID)
{
	m_NextSceneID = sceneID;
	Fade::FadeOut();
}

// EOF