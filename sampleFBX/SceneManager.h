/**
 * @file SceneManager
 * @brief シーンマネージャークラス
 */
#pragma once
#include "Singleton.h"
#include "ShadowCamera.h"

// 前方宣言
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

	std::unique_ptr<ShadowCamera> g_shadowCamera;
	int m_FPS;

public:
	/**
	 * @brief コンストラクタ
	 */
	SceneManager();

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Init();

	/**
	 * @brief 終了処理
	 * @return なし
	 */
	void Uninit();

	/**
	 * @brief 更新処理
	 * @return  なし
	 */
	void Update();

	/**
	 * @brief 描画処理
	 * @return  なし
	 */
	void Draw();

	/**
	 * @brief デフォルトのカメラを設定
	 * @return なし
	 */
	void SetDefCamera();

	/**
	 * @brief シーンチェンジ
	 * @return なし
	 */
	void Change();

	/**
	 * @brief シーンチェンジ
	 * @param sceneID 移動先のシーンのID
	 * @return なし
	 */
	static void Change(ESCENE sceneID);

	ShadowCamera* GetShadowCamera() {
		return g_shadowCamera.get();
	}

	void SetFPS(int nFPS) { m_FPS = (nFPS); }
};

// EOF