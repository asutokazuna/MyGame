/**
 * @file SceneManager
 * @brief シーンマネージャークラス
 */
#include "SceneManager.h"
#include "SceneGame.h"
#include "Scene.h"
#include "ModelData.h"
#include "Graphics.h"
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
#include "Sound.h"
#include "CollisionManager.h"

CScene* SceneManager::m_nowScene = nullptr;
int SceneManager::m_SceneID = 0;
int SceneManager::m_NextSceneID = 0;

/**
 * @brief コンストラクタ
 */
SceneManager::SceneManager(): m_pCamera(nullptr),m_pSky(nullptr), m_FPS(0)
{
}

/**
 * @brief 初期化処理
 * @return なし
 */
void SceneManager::Init()
{
	ShaderData::Init();
	TextureData::Init();
	ModelData::Init();
	CSound::Init();
	CollisionManager::GetInstance().Init();

	// 全オブジェクト初期化
	m_pCamera = new CCamera();
	CCamera::Set(m_pCamera);
	m_pCamera->Awake();
	m_pCamera->Init();

	m_pSky = new CSky();
	m_pSky->Init();
	Fade::Init();

	m_nowScene = new SceneTitle();
	m_nowScene->Awake();
	//ObjectManager::GetInstance().Awake();

	m_nowScene->Init();
	ObjectManager::GetInstance().Init();
}

/**
 * @brief 終了処理
 * @return なし
 */
void SceneManager::Uninit()
{
	ObjectManager::GetInstance().Uninit();

	if(m_nowScene)
	m_nowScene->Uninit();


	if(m_pSky)
	m_pSky->Uninit();
	if(m_pCamera)
	m_pCamera->Uninit();
	CollisionManager::GetInstance().Uninit();
	CSound::Fin();
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
	CSound::Update();
	if (Fade::IsFade() == true) {
		return;
	}
	Change();

	if (Fade::IsFade() == true) {
		return;
	}

	ObjectManager::GetInstance().Update();
	m_nowScene->Update();
	//CCamera::Get()->Update();

	CollisionManager::GetInstance().Check();

	ObjectManager::GetInstance().LastUpdate();
}

/**
 * @brief 描画処理
 * @return  なし
 */
void SceneManager::Draw()
{	
#ifdef _DEBUG
	//if (ImGui::TreeNode("FPS")) {
		ImGui::Text("FPS%d", m_FPS);
		//ImGui::TreePop();
	//}
#endif
	m_pSky->Draw();
	//CCamera::Get()->Draw();
	m_nowScene->Draw();

	ObjectManager::GetInstance().Draw();
	CollisionManager::GetInstance().Draw();
	Fade::Draw();
}

/**
 * @brief デフォルトのカメラを設定
 * @return なし
 */
void SceneManager::SetDefCamera()
{
	CCamera::Set(m_pCamera);
	m_pCamera->Awake();
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

	ObjectManager::GetInstance().Uninit();
	CollisionManager::GetInstance().Uninit();
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
	//ObjectManager::GetInstance().Awake();

	m_nowScene->Init();

	ObjectManager::GetInstance().Init();
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