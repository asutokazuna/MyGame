#pragma once
#include "Component.h"
#include "Graphics.h"
#include <string>
#include "MyMath.h"

class ShaderInfo :public Component
{
public:

	typedef struct {
		XMFLOAT4	Diffuse;		// Diffuse color RGBA
		XMFLOAT4	Ambient;		// Ambient color RGB
		XMFLOAT4	Specular;		// Specular 'shininess'
		XMFLOAT4	Emissive;		// Emissive color RGB
		float		Power;			// Sharpness if specular highlight
	} MATERIAL;

protected:
	int m_VSKind;	// 頂点シェーダの種類種
	int m_HSKind;	// ハルシェーダの種類種
	int m_DSKind;	// ドメインシェーダの種類種
	int m_GSKind;	// ジオメトリシェーダの種類種
	int m_PSKind;	// ピクセルシェーダの種類種
	int m_VSMax;
	int m_PSMax;	// 最大数
	ID3D11Buffer** m_VertexConstant;
	ID3D11Buffer** m_PixelConstant;
	ID3D11Buffer** m_HullConstant;
	ID3D11Buffer** m_DomainConstant;
	ID3D11Buffer** m_GeometryConstant;
	MATERIAL* m_material;
public:
	ShaderInfo();
	virtual ~ShaderInfo();
	//
	//void Uninit();

	//virtual void Draw() = 0;

	virtual void UpdateConstant(){}

	template<typename T>
	bool CreateConstantBuffer(ID3D11Buffer** buffer)
	{
		HRESULT hr;
		ID3D11Device* pDevice = CGraphics::GetDevice();
		// 定数バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(T);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		hr = pDevice->CreateBuffer(&bd, nullptr, buffer);
		if (FAILED(hr)) return false;
	}

	void SetShader();

	ShaderInfo* ChangeColor(XMFLOAT3 color);

	ShaderInfo* ChangeColor(Vector3 color);

	ShaderInfo* ChangeColor(float r, float g, float b);

	ShaderInfo* ChangeColor(XMFLOAT4 color);

	ShaderInfo* ChangeColor(float r, float g, float b, float a);

	ShaderInfo* ChangeAlpha(float alpha);

	virtual void SetFloat(std::string key, float value){}
	virtual void SetFloat(std::string key, XMFLOAT4 value){}
	virtual void SetFloat(std::string key, XMFLOAT4X4 value){}

	MATERIAL& GetMaterial() {
		return *m_material;
	}
};

// EOF