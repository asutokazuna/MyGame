/**
 * @file SceneResult
 * @brief リザルトシーンクラス
 */
#pragma once
#include "Scene.h"

// 前方宣言
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
	void Awake();

	/**
	 * @brief 更新処理
	 * @return  なし
	 */
	void Update();

#ifdef _DEBUG

	void Draw();
#endif // _DEBUG

};

// EOF