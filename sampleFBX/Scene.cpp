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
