/**
 * @file SceneTitle
 * @brief タイトルシーンクラス
 */
#pragma once
#include "Scene.h"

class TitleUI;
class GameObject;
class TitleCamera;

/**
 * @class SceneTitle
 * @brief タイトルシーン
 */
class SceneTitle :public CScene
{
private:
	TitleUI* m_UI;				//!< UI
	GameObject* m_stateMachine;	//!< ステートマシン
	TitleCamera* m_camera;		//!< カメラ
public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 更新処理
	 * @return  なし
	 */
	void Update();
};

// EOF