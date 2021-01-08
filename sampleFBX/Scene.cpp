#include "Scene.h"
#include "Graphics.h"

// 静的メンバ
CScene*	CScene::m_pScene = nullptr;

// コンストラクタ
CScene::CScene() : m_FPS(0)
{
	m_szDebug[0] = _T('\0');
}

// デストラクタ
CScene::~CScene()
{

}

void CScene::Awake()
{
}

// 初期化
HRESULT CScene::Init()
{
	HRESULT hr = S_OK;


	return hr;
}

// 終了処理
void CScene::Uninit()
{

}

// 更新
void CScene::Update()
{


}

// 描画
void CScene::Draw()
{
	m_szDebug[0] = _T('\0');	// デバッグ文字列初期化

	// FPS を画面に描画するための文字列を作成
	TCHAR	str[256];
	_stprintf_s(str, _countof(str), _T("FPS = %d\n"), m_FPS);
	lstrcat(m_szDebug, str);

	// カメラ反映
	//if (m_pCamera) {
	//	//m_pCamera->Draw();
	//}

	// 前面カリング (FBXは表裏が反転するため)
	CGraphics::SetCullMode(CULLMODE_CW);
	CGraphics::SetBlendState(BS_NONE);			// アルファ処理しない
	CGraphics::SetZWrite(true);



	CGraphics::SetZWrite(false);
	CGraphics::SetBlendState(BS_ALPHABLEND);	// 半透明描画
	
}

// シーン切替
void CScene::Set(CScene* pScene)
{
	// シーンの終了
	if (m_pScene) {
		m_pScene->Uninit();
	}

	// シーン入替
	m_pScene = pScene;

	// シーンの開始
	if (m_pScene) {
		m_pScene->Init();
	}
}

//=======================================================================================
//	End of File
//=======================================================================================
