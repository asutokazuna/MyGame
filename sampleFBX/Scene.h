//=======================================================================================
//
//	  �Q�[���V�[�� �N���X��` [Scene.h]
//
//=======================================================================================
#pragma once
#include <Windows.h>
#include "Object.h"
#include <list>

class CScene
{
protected:
	static CScene*	m_pScene;		// �A�N�e�B�u �V�[��

	TCHAR		m_szDebug[1024];	// �f�o�b�O�p������
	int			m_FPS;				// �t���[�����J�E���g�p

	//-------- �Q�[���p�I�u�W�F�N�g
	std::list<Object*>	m_pObj;				// �I�u�W�F�N�g�擪

public:
	CScene();
	virtual ~CScene();

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void SetFPS(int nFPS) { m_FPS = nFPS; }

	Object* GetObj() { return m_pObj.back(); }
	void SetObj(Object* pObj) { m_pObj.push_back(pObj); }

	static CScene* Get() { return m_pScene; }
	static void Set(CScene* pScene);
};

//=======================================================================================
//	End of File
//=======================================================================================
