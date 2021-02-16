//=============================================================================
//
// メイン処理 [main.cpp]
//
//=============================================================================
#include "GameWnd.h"

//-------- ライブラリのリンク
#pragma comment(lib, "winmm")
#pragma comment(lib, "d3d11")

namespace {
	const TCHAR g_szCaption[] = _T("Shooting");	// キャプション
}

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	// ウィンドウを作成
	int nResult = EXIT_FAILURE;
	CGameWindow* pWnd = new CGameWindow();
	if (pWnd->CreateFrame(g_szCaption,				// ウィンドウ キャプション
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, 0,	// ウィンドウ スタイル，拡張スタイル
		CW_USEDEFAULT, CW_USEDEFAULT,				// ウィンドウ位置
		SCREEN_WIDTH, SCREEN_HEIGHT)) {				// クライアント領域サイズ
		pWnd->Show(iCmdShow);							// ウィンドウを表示
		pWnd->Update();									// ウィンドウ表示を更新
		nResult = pWnd->Run();							// メッセージ ループ
	}
	delete pWnd;
	return nResult;
}

// EOF