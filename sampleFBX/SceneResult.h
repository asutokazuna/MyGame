/**
 * @file SceneResult
 * @brief リザルトシーンクラス
 */
#pragma once
#include "Scene.h"

class GameObject;

class SceneResult :public CScene
{
private:
	GameObject* m_Press;
	GameObject* m_Win;
	GameObject* m_Lose;
public:
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
};

// EOF