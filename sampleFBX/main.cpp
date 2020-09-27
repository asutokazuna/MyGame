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
//
////=============================================================================
//// WM_CREATEメッセージハンドラ
////=============================================================================
//int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs)
//{
//	// クライアント領域サイズをSCREEN_WIDTH×SCREEN_HEIGHTに再設定.
//	RECT rcClnt;
//	GetClientRect(hWnd, &rcClnt);
//	rcClnt.right -= rcClnt.left;
//	rcClnt.bottom -= rcClnt.top;
//	if (rcClnt.right != SCREEN_WIDTH || rcClnt.bottom != SCREEN_HEIGHT) {
//		RECT rcWnd;
//		GetWindowRect(hWnd, &rcWnd);
//		SIZE sizeWnd;
//		sizeWnd.cx = (rcWnd.right - rcWnd.left) - rcClnt.right + SCREEN_WIDTH;
//		sizeWnd.cy = (rcWnd.bottom - rcWnd.top) - rcClnt.bottom + SCREEN_HEIGHT;
//		SetWindowPos(hWnd, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
//	}
//
//	// IME無効化
//	ImmAssociateContext(hWnd, nullptr);
//
//	return 0;	// -1を返すとCreateWindow[Ex]が失敗する.
//}
//
////=============================================================================
//// 初期化処理
////=============================================================================
//HRESULT Init(HWND hWnd, BOOL bWindow)
//{
//	HRESULT hr = S_OK;
//
//	// カメラ初期化
//	hr = g_camera.Init();
//	if (FAILED(hr))
//		return hr;
//	CCamera::Set(&g_camera);
//	hr = g_cameraTP.Init();
//	if (FAILED(hr))
//		return hr;
//	hr = g_cameraFP.Init();
//	if (FAILED(hr))
//		return hr;
//	hr = g_cameraBT.Init();
//	if (FAILED(hr))
//		return hr;
//
//	// 敵機初期化
//	XMFLOAT4X4 mWorld(-1.0f, 0.0f, 0.0f, 0.0f,
//					   0.0f,1.0f,0.0f, 0.0f,
//					   0.0f,  0.0f, -1.0f, 0.0f,
//					   0.0f, 0.0f, 5000.0f, 1.0f);
//	for (int i = 0; i < MAX_ENEMY; ++i)
//	{
//		//hr = g_enemy[i].Init();
//		//	if (FAILED(hr)) {
//		//		return hr;
//		//	}
//		//	mWorld._41 = (2 - i) * 1000.0f;
//		//	g_enemy[i].SetWorld(mWorld);
//	}
//
//	return hr;
//}
//
////=============================================================================
//// 更新処理
////=============================================================================
//void Update(void)
//{
//	// 入力処理更新
//	//CInput::Update();	// 必ずUpdate関数の先頭で実行.
//
//	// デバッグ文字列表示更新
////	UpdateDebugProc();
//
//	// デバッグ文字列設定
////	StartDebugProc();
////	PrintDebugProc("FPS:%d\n\n", g_nCountFPS);
//
//	// ポリゴン表示更新
//	//UpdatePolygon();
//	
//	// カメラ更新
//	//if (CInput::GetKeyTrigger(VK_0) || CInput::GetKeyTrigger(VK_NUMPAD0)){
//	//	CCamera::Set(&g_camera);
//	//}
//	//if (CInput::GetKeyTrigger(VK_1) || CInput::GetKeyTrigger(VK_NUMPAD1)){
//	//	CCamera::Set(&g_cameraFP);
//	//}
//	//if (CInput::GetKeyTrigger(VK_2) || CInput::GetKeyTrigger(VK_NUMPAD2)){
//	//	CCamera::Set(&g_cameraBT);
//	//}
//	//if (CInput::GetKeyTrigger(VK_3) || CInput::GetKeyTrigger(VK_NUMPAD3)){
//	//	CCamera::Set(&g_cameraTP);
//	//}
//	CCamera::Get()->Update();
//}

// EOF