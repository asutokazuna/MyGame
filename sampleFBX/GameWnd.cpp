//=======================================================================================
//
//	  ゲーム用ウィンドウ クラス定義 [GameWnd.cpp]
//
//=======================================================================================
#include "GameWnd.h"
#include "Graphics.h"
#include "input.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

//-------- ライブラリのリンク
#pragma comment(lib, "imm32")

SceneManager* CGameWindow::m_pScene = nullptr;

//---------------------------------------------------------------------------------------
//	ウィンドウ初期化
//---------------------------------------------------------------------------------------
bool CGameWindow::InitInstance()
{
	// IME 無効化
	::ImmAssociateContext(GetHwnd(), NULL);

	if (!CWindow::InitInstance()) return false;

	m_bWindow = true;
	//int nID = MessageBox(_T("ウィンドウモードで実行しますか？"), _T("画面モード"), MB_YESNOCANCEL);
	//if (nID == IDCANCEL) return false;
	//if (nID == IDNO) m_bWindow = false;

	::timeBeginPeriod(1);	// タイマの分解能を最小にセット

	// グラフィックデバイス初期化
	if (FAILED(CGraphics::Init(GetHwnd(), SCREEN_WIDTH, SCREEN_HEIGHT, m_bWindow)))
		return false;
#if _DEBUG
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsLight();

	HWND hWnd = GetHwnd();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(CGraphics::GetDevice(), CGraphics::GetDeviceContext());
#endif

	// 入力初期化
	CInput::Init();

	// シーン初期化
	//m_pScene = new SceneManager();//CScene::Create(m_pGraph);
	//if (!m_pScene) {
	//	return false;
	//}
	SceneManager::GetInstance().Init();
	//CScene::Set(m_pScene);


	m_dwFPSLastTime = ::timeGetTime();
	m_dwExecLastTime = m_dwFPSLastTime - (1000/FRAME_RATE);
	m_dwFrameCount = 0;

	return true;
}

//---------------------------------------------------------------------------------------
//	ウィンドウ解放
//---------------------------------------------------------------------------------------
int CGameWindow::ExitInstance()
{
	SceneManager::GetInstance().Uninit();
	// シーン解放
	//delete m_pScene;

	// 入力終了処理
	CInput::Uninit();

#if _DEBUG
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
#endif

	// グラフィック デバイス解放
	CGraphics::Uninit();

	::timeEndPeriod(1);				// タイマの分解能を元に戻す

	return CWindow::ExitInstance();	// 実行ファイルの戻り値
}

//---------------------------------------------------------------------------------------
//	アイドル時処理
//---------------------------------------------------------------------------------------
bool CGameWindow::OnIdle(long lCount)
{
	// この辺でフレーム数カウント
	DWORD dwCurrentTime = ::timeGetTime();			// 現在のタイマ値を取得
	if (dwCurrentTime - m_dwFPSLastTime >= 500) {	// 0.5 秒ごとに計測
		// フレーム数を計算
		//if (m_pScene) {
		//	m_pScene->SetFPS(m_dwFrameCount * 1000 / (dwCurrentTime - m_dwFPSLastTime));
		//}
		m_dwFPSLastTime = dwCurrentTime;	// タイマ値を更新
		m_dwFrameCount = 0;					// フレームカウンタをリセット
	}
	// この辺で時間管理
	while (dwCurrentTime - m_dwExecLastTime >= (1000/FRAME_RATE)) {
		m_dwExecLastTime += (1000/FRAME_RATE);
		CInput::Update();				// 入力処理更新
		if (&SceneManager::GetInstance()) {
			SceneManager::GetInstance().Update();			// ゲーム メイン処理
		}
	}

#if _DEBUG
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
#endif

	CGraphics::Draw(&SceneManager::GetInstance());		// レンダリング処理


	m_dwFrameCount++;					// フレームカウント＋１
	return true;
}

//---------------------------------------------------------------------------------------
//	WM_KEYDOWN ハンドラ
//---------------------------------------------------------------------------------------
void CGameWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
//#if _DEBUG
	// [Esc] が押されていたら
	if (nChar == VK_ESCAPE) {
		// ウィンドウを閉じる
		OnClose();
	}
//#endif
}

//---------------------------------------------------------------------------------------
//	WM_ERASEBKGND ハンドラ
//---------------------------------------------------------------------------------------
bool CGameWindow::OnEraseBkgnd(HDC hdc)
{
	// 背景消去しないで消去済みとして返す
	return true;
}

//---------------------------------------------------------------------------------------
//	WM_SETCURSOR ハンドラ
//---------------------------------------------------------------------------------------
bool CGameWindow::OnSetCursor(HWND hwnd, UINT nHitTest, UINT uMouseMsg)
{
	// 全画面モードか、マウスカーソル座標がクライアント領域内なら
	if (!m_bWindow || nHitTest == HTCLIENT) {
		// マウスカーソル消去
		::SetCursor(NULL);
		return true;
	}
	return false;
}

#if _DEBUG
LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif 

LRESULT CGameWindow::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = GetHwnd();

#if _DEBUG
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;
#endif
	return CWindow::WndProc(uMsg, wParam, lParam);
}
//=======================================================================================
//	End of File
//=======================================================================================
