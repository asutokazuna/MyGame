/**
 * @file TitleUI
 * @brief タイトルのUIクラス
 */
#pragma once
#include "GameObject.h"

// 前方宣言
class UIMesh;

/**
 * @class TitleUI
 * @brief タイトルに出てくるUI
 */
class TitleUI :public GameObject
{
private:
	GameObject* m_RogoMesh;		//!< タイトルロゴ
	GameObject* m_StartMesh;	//!< スタートボタン

public:
	/**
	 * @breif 初期化処理
	 * @return なし
	 */
	void Awake();
};

// EOF