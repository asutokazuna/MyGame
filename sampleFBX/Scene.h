//=======================================================================================
//
//	  ゲームシーン クラス定義 [Scene.h]
//
//=======================================================================================
#pragma once
#include <Windows.h>
#include "Object.h"
#include <list>

class CScene
{
protected:
	static CScene*	m_pScene;		// アクティブ シーン

	TCHAR		m_szDebug[1024];	// デバッグ用文字列
	int			m_FPS;				// フレーム数カウント用

public:
	CScene();
	virtual ~CScene();

	virtual void Awake();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void SetFPS(int nFPS) { 
		m_FPS = nFPS; 
	}
	
	static CScene* Get() { return m_pScene; }
	static void Set(CScene* pScene);
};

//=======================================================================================
//	End of File
//=======================================================================================
