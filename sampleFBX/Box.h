/**
 * @file Box.h
 * @brief 境界ボックスデバッグ表示
 */
#pragma once
#include "main.h"
#include "Graphics.h"

class CBox
{
private:
	ID3D11Buffer* m_pVertexBuffer;	// 頂点バッファ
	XMFLOAT4X4 m_world;
	XMFLOAT4 m_color;		//!< 色
	static ID3D11Buffer* m_pConstantBuffer[2];		// 定数バッファ
	static ID3D11VertexShader* m_pVertexShader;		// 頂点シェーダ
	static ID3D11InputLayout* m_pInputLayout;		// 頂点フォーマット
	static ID3D11PixelShader* m_pPixelShader;		// ピクセルシェーダ
	static ID3D11Buffer*	m_pIndexBuffer;
	static int m_nRef;	//!< 参照カウンタ
public:
	CBox();
	~CBox();

	HRESULT Init(XMFLOAT3* pHalfSize);
	void Uninit();
	void Update();
	void Draw();

	XMFLOAT4X4& GetWorld() { return m_world; }
	void SetWorld(XMFLOAT4X4 world) { m_world = world; }
	XMFLOAT4& GetColor() { return m_color; }
	void SetColor(XMFLOAT4* pColor) { m_color = *pColor; }
};

// EOF