/**
 * @file SceneResult
 * @brief リザルトシーンクラス
 */
#pragma once
#include "Scene.h"

class GameObject;

/**
 * @class SceneResult
 * @biref リザルトシーン
 */
class SceneResult :public CScene
{
private:
	GameObject* m_Press;
	GameObject* m_Win;
	GameObject* m_Lose;
public:

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT Init();

	/**
	 * @brief 更新処理
	 * @return  なし
	 */
	void Update();
};

// EOF