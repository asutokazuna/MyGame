//=======================================================================================
//
//	  DirectX11 Graphics クラス [Graphics.cpp]
//
//=======================================================================================
#include "Graphics.h"
#include "SceneManager.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ObjectRenderer.h"

//-------- ライブラリのリンク
#pragma comment(lib, "d3d11")

// 静的メンバ
ID3D11Device*				CGraphics::m_pDevice;				// デバイス
ID3D11DeviceContext*		CGraphics::m_pDeviceContext;		// デバイス コンテキスト
IDXGISwapChain*				CGraphics::m_pSwapChain;			// スワップチェーン
ID3D11RenderTargetView*		CGraphics::m_pRenderTargetView;		// フレームバッファ
ID3D11Texture2D*			CGraphics::m_pDepthStencilTexture;	// Zバッファ用メモリ
ID3D11DepthStencilView*		CGraphics::m_pDepthStencilView;		// Zバッファ
UINT						CGraphics::m_uSyncInterval = 0;		// 垂直同期 (0:無, 1:有)
ID3D11RasterizerState*		CGraphics::m_pRs[MAX_CULLMODE];		// ラスタライザ ステート
ID3D11BlendState*			CGraphics::m_pBlendState[MAX_BLENDSTATE];// ブレンド ステート
ID3D11DepthStencilState*	CGraphics::m_pDSS[2];				// Zバッファ/ステンシル ステート
ID3D11SamplerState*			CGraphics::m_pSamplerState;		// テクスチャ サンプラ1Buffer
ID3D11SamplerState*			CGraphics::m_pSamplerStateShadow;		// テクスチャ サンプラ1Buffer

ID3D11DepthStencilView*		CGraphics::m_pDepthStencliViewShadow;
ID3D11ShaderResourceView*	CGraphics::m_ShadowTexture;
ID3D11Texture2D*			CGraphics::m_pDepthStencilTextureShadow;

D3D11_VIEWPORT CGraphics::m_ViewPort[2];
static const int SHADOW_TEX_SIZE = 1024 * 4;

// グラフィック環境の初期化
HRESULT CGraphics::Init(HWND hWnd, int nWidth, int nHeight, bool bWindow)
{
	HRESULT hr = S_OK;

	// デバイス、スワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Width = SCREEN_WIDTH;
	scd.BufferDesc.Height = SCREEN_HEIGHT;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = bWindow;

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, 0, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, &scd,
		&m_pSwapChain, &m_pDevice, nullptr, &m_pDeviceContext);
	if (FAILED(hr)) {
		return hr;
	}

	// バックバッファ生成
	hr = CreateBackBuffer();
	if (FAILED(hr)) {
		return hr;
	}

	// ラスタライズ設定
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;	// カリング無し(両面描画)
	m_pDevice->CreateRasterizerState(&rd, &m_pRs[0]);
	rd.CullMode = D3D11_CULL_FRONT;	// 前面カリング(裏面描画)
	m_pDevice->CreateRasterizerState(&rd, &m_pRs[1]);
	rd.CullMode = D3D11_CULL_BACK;	// 背面カリング(表面描画)
	m_pDevice->CreateRasterizerState(&rd, &m_pRs[2]);
	SetCullMode(CULLMODE_CCW);

	// ブレンド ステート生成
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState[0]);
	// ブレンド ステート生成 (アルファ ブレンド用)
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState[1]);
	// ブレンド ステート生成 (加算合成用)
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState[2]);
	// ブレンド ステート生成 (減算合成用)
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState[3]);
	SetBlendState(BS_ALPHABLEND);

	// 深度ステンシルステート生成
	CD3D11_DEFAULT def;
	CD3D11_DEPTH_STENCIL_DESC dsd(def);
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	m_pDevice->CreateDepthStencilState(&dsd, &m_pDSS[0]);
	CD3D11_DEPTH_STENCIL_DESC dsd2(def);
	dsd2.DepthEnable = FALSE;
	m_pDevice->CreateDepthStencilState(&dsd2, &m_pDSS[1]);

	// テクスチャ サンプラ生成
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	hr = m_pDevice->CreateSamplerState(&sd, &m_pSamplerState);
	if (FAILED(hr)) {
		return hr;
	}
	sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = m_pDevice->CreateSamplerState(&sd, &m_pSamplerStateShadow);
	if (FAILED(hr)) {
		return hr;
	}
	return hr;
}

// グラフィック環境のクリーンアップ
void CGraphics::Uninit()
{
	// テクスチャ サンプラの開放
	SAFE_RELEASE(m_pSamplerStateShadow);
	SAFE_RELEASE(m_pSamplerState);

	// 深度ステンシルステート解放
	for (int i = 0; i < _countof(m_pDSS); ++i) {
		SAFE_RELEASE(m_pDSS[i]);
	}

	// ブレンド ステート解放
	for (int i = 0; i < MAX_BLENDSTATE; ++i) {
		SAFE_RELEASE(m_pBlendState[i]);
	}

	// ラスタライザ ステート解放
	for (int i = 0; i < MAX_CULLMODE; ++i) {
		SAFE_RELEASE(m_pRs[i]);
	}

	// バックバッファ解放
	ReleaseBackBuffer();

	// スワップチェーン解放
	SAFE_RELEASE(m_pSwapChain);

	// デバイス コンテキストの開放
	SAFE_RELEASE(m_pDeviceContext);

	// デバイスの開放
	SAFE_RELEASE(m_pDevice);
}

// バックバッファ生成
HRESULT CGraphics::CreateBackBuffer()
{
	HRESULT hr = S_OK;

	// レンダーターゲットビュー生成
	ID3D11Texture2D* pBackBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	hr = m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
	SAFE_RELEASE(pBackBuffer);
	if (FAILED(hr)) {
		return hr;
	}

	// Zバッファ用テクスチャ生成
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = SCREEN_WIDTH;
	td.Height = SCREEN_HEIGHT;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	hr = m_pDevice->CreateTexture2D(&td, nullptr, &m_pDepthStencilTexture);
	if (FAILED(hr)) {
		return hr;
	}

	// Zバッファターゲットビュー生成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = td.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture, &dsvd, &m_pDepthStencilView);
	if (FAILED(hr)) {
		return hr;
	}

	//--- テクスチャ
	// 設定
	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;
	texDesc.Width	= SHADOW_TEX_SIZE ;
	texDesc.Height	= SHADOW_TEX_SIZE ;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Count = 1;
	// 生成
	hr = m_pDevice->CreateTexture2D(&texDesc, NULL, &m_pDepthStencilTextureShadow);
	if (FAILED(hr)) { return E_FAIL; }

	//--- デプスステンシル
	// 設定
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	// 生成
	hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilTextureShadow, &dsvDesc, &m_pDepthStencliViewShadow);
	if (FAILED(hr)) { return E_FAIL; }

	//--- シェーダリソース
	// 設定
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	// 生成
	hr = m_pDevice->CreateShaderResourceView(m_pDepthStencilTextureShadow, &srvDesc, &m_ShadowTexture);
	if (FAILED(hr)) { return E_FAIL; }


	// 各ターゲットビューをレンダーターゲットに設定
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	// ビューポート設定
	// ウィンドウ描画
	m_ViewPort[0].Width = (float)SCREEN_WIDTH;
	m_ViewPort[0].Height = (float)SCREEN_HEIGHT;
	m_ViewPort[0].MinDepth = 0.0f;
	m_ViewPort[0].MaxDepth = 1.0f;
	m_ViewPort[0].TopLeftX = 0;
	m_ViewPort[0].TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &m_ViewPort[0]);
	// 深度バッファテクスチャ
	m_ViewPort[1].Width		= (float)SHADOW_TEX_SIZE;
	m_ViewPort[1].Height	= (float)SHADOW_TEX_SIZE;
	m_ViewPort[1].MinDepth = 0.0f;
	m_ViewPort[1].MaxDepth = 1.0f;
	m_ViewPort[1].TopLeftX = 0;
	m_ViewPort[1].TopLeftY = 0;

	return hr;
}

// バックバッファ解放
void CGraphics::ReleaseBackBuffer()
{
	if (m_pDeviceContext) {
		m_pDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
	}
	SAFE_RELEASE(m_ShadowTexture);
	SAFE_RELEASE(m_pDepthStencilTextureShadow);
	SAFE_RELEASE(m_pDepthStencliViewShadow);
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_RELEASE(m_pDepthStencilTexture);
	SAFE_RELEASE(m_pRenderTargetView);
}

void CGraphics::Update()
{
}

void CGraphics::Draw(SceneManager* pScene)
{
	// バックバッファ＆Ｚバッファのクリア
	float ClearColor[4] = { 0.117647f, 0.254902f, 0.352941f, 1.0f };

	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencliViewShadow, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);
	m_pDeviceContext->PSSetSamplers(1, 1, &m_pSamplerStateShadow);

#if _DEBUG
	ImGui::Begin("DebugWindow");
#endif
	// シーンの描画
	if (pScene) {
		pScene->Draw();
	}

#if _DEBUG
	ImVec2 size = { 300,300 };
	ImGui::Image(m_ShadowTexture, size);
	ImGui::End();
#endif
#if _DEBUG
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
#endif
	// バックバッファとフロントバッファの入れ替え
	m_pSwapChain->Present(m_uSyncInterval, 0);

}

void CGraphics::SetViewport(int kind)
{
	m_pDeviceContext->RSSetViewports(1, &m_ViewPort[kind]);
	m_pDeviceContext->OMSetRenderTargets(0, nullptr, m_pDepthStencliViewShadow);
}

void CGraphics::SetDrawShadow()
{
	m_pDeviceContext->RSSetViewports(1, &m_ViewPort[1]);
	m_pDeviceContext->OMSetRenderTargets(0, nullptr, m_pDepthStencliViewShadow);
}

void CGraphics::SetDrawDefauolt()
{
	m_pDeviceContext->RSSetViewports(1, &m_ViewPort[0]);
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	m_pDeviceContext->PSSetShaderResources(3, 1, &m_ShadowTexture);
}

// 深度バッファ有効無効制御
void CGraphics::SetZBuffer(bool bEnable)
{
	m_pDeviceContext->OMSetDepthStencilState((bEnable) ? nullptr : m_pDSS[1], 0);
}

// 深度バッファ更新有効無効制御
void CGraphics::SetZWrite(bool bEnable)
{
	m_pDeviceContext->OMSetDepthStencilState((bEnable) ? nullptr : m_pDSS[0], 0);
}

// ブレンドステート設定
void CGraphics::SetBlendState(int nBlendState)
{
	if (nBlendState >= 0 && nBlendState < MAX_BLENDSTATE) {
		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		m_pDeviceContext->OMSetBlendState(m_pBlendState[nBlendState], blendFactor, 0xffffffff);
	}
}

// カリング設定
void CGraphics::SetCullMode(int nCullMode)
{
	if (nCullMode >= 0 && nCullMode < MAX_CULLMODE) {
		m_pDeviceContext->RSSetState(m_pRs[nCullMode]);
	}
}

void CGraphics::SetDepthShadowDSV()
{
	// 各ターゲットビューをレンダーターゲットに設定
}

void CGraphics::SetDefaultDSV()
{
	// 各ターゲットビューをレンダーターゲットに設定

}
