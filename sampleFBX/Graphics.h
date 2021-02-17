//=======================================================================================
//
//	  DirectX11 Graphics クラス定義 [Graphics.h]
//
//=======================================================================================
#pragma once
#include "Main.h"

enum EBlendState {
	BS_NONE = 0,		// 半透明合成無し
	BS_ALPHABLEND,		// 半透明合成
	BS_ADDITIVE,		// 加算合成
	BS_SUBTRACTION,		// 減算合成

	MAX_BLENDSTATE
};

enum ECullMode {
	CULLMODE_NONE = 0,	// カリングしない
	CULLMODE_CW,		// 前面カリング
	CULLMODE_CCW,		// 背面カリング

	MAX_CULLMODE
};

class SceneManager;
class CGraphics
{
private:
	static ID3D11Device*			m_pDevice;				// デバイス
	static ID3D11DeviceContext*		m_pDeviceContext;		// デバイス コンテキスト
	static IDXGISwapChain*			m_pSwapChain;			// スワップチェーン
	static ID3D11RenderTargetView*	m_pRenderTargetView;	// フレームバッファ
	static ID3D11Texture2D*			m_pDepthStencilTexture;	// Zバッファ用メモリ
	static ID3D11DepthStencilView*	m_pDepthStencilView;	// Zバッファ
	static UINT						m_uSyncInterval;		// 垂直同期 (0:無, 1:有)
	static ID3D11RasterizerState*	m_pRs[MAX_CULLMODE];	// ラスタライザ ステート
	static ID3D11BlendState*		m_pBlendState[MAX_BLENDSTATE];// ブレンド ステート
	static ID3D11DepthStencilState*	m_pDSS[2];				// Zバッファ/ステンシル ステート
	static ID3D11SamplerState*		m_pSamplerState;		// テクスチャ サンプラ
	static ID3D11SamplerState*		m_pSamplerStateShadow;		// テクスチャ サンプラ

	static ID3D11DepthStencilView*	m_pDepthStencliViewShadow;
	static ID3D11ShaderResourceView* m_ShadowTexture;
	static ID3D11Texture2D*			m_pDepthStencilTextureShadow;
	static D3D11_VIEWPORT m_ViewPort[2];

private:
	static HRESULT CreateBackBuffer();
	static void ReleaseBackBuffer();

public:
	static HRESULT Init(HWND hWnd, int nWidth, int nHeight, bool bWindow);
	static void Uninit();
	static void Update();
	static void Draw(SceneManager* pScene);

	static ID3D11Device* GetDevice() { return m_pDevice; }
	static ID3D11DeviceContext* GetDeviceContext() { return m_pDeviceContext; }
	static ID3D11DeviceContext* GetContext() { return m_pDeviceContext; }
	static ID3D11SamplerState* GetSamplerState() { return m_pSamplerState; }
	static ID3D11SamplerState* GetSamplerStateShadow() { return m_pSamplerStateShadow; }
	static void SetViewport(int kind);
	static void SetDrawShadow();
	static void SetDrawDefauolt();
	static void SetZBuffer(bool bEnable);
	static void SetZWrite(bool bEnable);
	static void SetBlendState(int nBlendState);
	static void SetCullMode(int nCullMode);

	static void SetDepthShadowDSV();
	static void SetDefaultDSV();
};
