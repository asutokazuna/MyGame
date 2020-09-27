/**
 * @file SceneManager
 * @brief シーンマネージャークラス
 */
#pragma once
#include "Singleton.h"

class CScene;
class CCamera;
class CSky;

/**
 * @class SceneManager
 * @brief シーン管理クラス
 */
class SceneManager:public Singleton<SceneManager>
{
public:
	friend class Singleton<SceneManager>;		//!< シングルトン

public:
	enum ESCENE
	{
		SCENE_TITLE,
		SCENE_GAME,
		SCENE_RESULT,
		SCENE_MAX
	};

private:
	static CScene* m_nowScene;
	static int m_SceneID;
	static int m_NextSceneID;

	CCamera*	m_pCamera;			// アクティブなカメラ
	CSky*	m_pSky;

public:
	SceneManager();
	~SceneManager();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetDefCamera();

	void Change();
	static void Change(ESCENE sceneID);
};

// EOF