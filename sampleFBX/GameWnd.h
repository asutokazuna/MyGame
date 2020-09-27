//=======================================================================================
//
//	  �Q�[���p�E�B���h�E �N���X��` [GameWnd.h]
//
//=======================================================================================
#pragma once
#include "Window.h"

class SceneManager;
class CGameWindow : public CWindow
{
private:
	bool		m_bWindow;			// �E�B���h�E / �t���X�N���[��

	DWORD		m_dwExecLastTime;	// FPS�v���p
	DWORD		m_dwFPSLastTime;
	DWORD		m_dwFrameCount;

	static SceneManager* m_pScene;

public:
	bool InitInstance();
	int ExitInstance();
	bool OnIdle(long lCount);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	bool OnEraseBkgnd(HDC hdc);
	bool OnSetCursor(HWND hwnd, UINT nHitTest, UINT uMouseMsg);

	LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

//=======================================================================================
//	End of File
//=======================================================================================
