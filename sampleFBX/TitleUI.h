/**
 * @file TitleUI
 * @brief タイトルのUIクラス
 */
#pragma once
#include "GameObject.h"

class UIMesh;
class TitleUI :public GameObject
{
private:
	GameObject* m_RogoMesh;
	GameObject* m_StartMesh;
public:
	TitleUI();
	~TitleUI();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
};

// EOF