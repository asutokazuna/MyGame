/**
 * @file SceneManager
 * @brief �V�[���}�l�[�W���[�N���X
 */
#pragma once
#include "Singleton.h"

class CScene;
class CCamera;
class CSky;

/**
 * @class SceneManager
 * @brief �V�[���Ǘ��N���X
 */
class SceneManager:public Singleton<SceneManager>
{
public:
	friend class Singleton<SceneManager>;		//!< �V���O���g��

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

	CCamera*	m_pCamera;			// �A�N�e�B�u�ȃJ����
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