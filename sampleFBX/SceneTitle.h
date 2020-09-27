/**
 * @file SceneTitle
 * @brief �^�C�g���V�[���N���X
 */
#pragma once
#include "Scene.h"

class TitleUI;
class SceneTitle :public CScene
{
private:
	TitleUI* m_UI;
public:
	HRESULT Init();
	void Uninit();
	void Update();
};

// EOF