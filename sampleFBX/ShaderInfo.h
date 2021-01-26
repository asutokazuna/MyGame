#pragma once
#include "Component.h"
#include "Graphics.h"
#include <string>
#include "MyMath.h"
#include <unordered_map>
#include <memory>

enum ShaderKind
{
	VS,
	HS,
	DS,
	GS,
	PS,

	MAX
};

/**
 * @brief コンスタントバッファをラップしたクラス
 */
class ShaderBuffer
{
private:
	ID3D11Buffer* m_cbuffer;
	UINT m_size;

public:
	HRESULT CreateCBuffer(UINT size)
	{
		HRESULT hr;
		ID3D11Device* pDevice = CGraphics::GetDevice();
		m_size = size;
		// 定数バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = size;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags = 0;
		hr = pDevice->CreateBuffer(&bd, nullptr, &m_cbuffer);
		return hr;
	}

public:
	ShaderBuffer()
	{
		//CreateCBuffer();
	}

	~ShaderBuffer()
	{
		SAFE_RELEASE(m_cbuffer);
	}

	void Bind(int kind, UINT slot, void* data);
public:
	void BindVS(UINT slot)
	{
		ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
		pDeviceContext->VSSetConstantBuffers(slot, 1, &m_cbuffer);
	}
	void BindPS(UINT slot)
	{
		ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
		pDeviceContext->PSSetConstantBuffers(slot, 1, &m_cbuffer);
	}
	void BindGS(UINT slot)
	{
		ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
		pDeviceContext->GSSetConstantBuffers(slot, 1, &m_cbuffer);
	}
	void BindHS(UINT slot)
	{
		ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
		pDeviceContext->HSSetConstantBuffers(slot, 1, &m_cbuffer);
	}
	void BindDS(UINT slot)
	{
		ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
		pDeviceContext->DSSetConstantBuffers(slot, 1, &m_cbuffer);
	}
	void Update()
	{
		//ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
		//D3D11_MAPPED_SUBRESOURCE pData;
		//if (SUCCEEDED(m_pDeviceContext->Map(m_cbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData))) {
		//	memcpy_s(pData.pData, pData.RowPitch, (void*)&m_data, sizeof(m_data));
		//	m_pDeviceContext->Unmap(m_cbuffer, 0);
		//}
	}
	void UpdateData(void* data);

};

class ShaderBufferManager
{
private:
	std::unordered_map<std::string, std::unique_ptr<ShaderBuffer>> m_buffList;
public:
	template <class T>
	void Create(std::string name)
	{
		m_buffList[name] = std::make_unique<ShaderBuffer>();
		m_buffList[name].get()->CreateCBuffer(sizeof(T));
	}

	void BindBuffer(std::string name, int shaderkind, void* data, UINT slot)
	{
		m_buffList[name].get()->Bind(shaderkind, slot, data);
	}


	static void BindCBuffer(std::string name, void* data)
	{

	}
};

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
	int m_VSKind;	// 頂点シェーダの種類
	int m_HSKind;	// ハルシェーダの種類
	int m_DSKind;	// ドメインシェーダの種類
	int m_GSKind;	// ジオメトリシェーダの種類
	int m_PSKind;	// ピクセルシェーダの種類
	MATERIAL* m_material;
	XMFLOAT4X4 m_TexWorld;
	ID3D11ShaderResourceView* m_pTexture;

	ShaderBufferManager m_cbufferManager;
public:
	ShaderInfo();
	virtual ~ShaderInfo();

	virtual void UpdateConstant() = 0;

	virtual void UpdateMatCBuffer(){}

	virtual void UpdateBoneCBuffer(){}

	template <class T>
	void CreateCBuffer(std::string name)
	{
		m_cbufferManager.Create<T>(name);
	}

	virtual void BindCBuffer(std::string name, int shaderkind, void *data, int slot)
	{
		m_cbufferManager.BindBuffer(name, shaderkind, data, slot);
	}

	void SetShader();

	ShaderInfo* ChangeColor(XMFLOAT3 color);

	ShaderInfo* ChangeColor(Vector3 color);

	ShaderInfo* ChangeColor(float r, float g, float b);

	ShaderInfo* ChangeColor(XMFLOAT4 color);

	ShaderInfo* ChangeColor(float r, float g, float b, float a);

	ShaderInfo* ChangeAlpha(float alpha);

	ShaderInfo* SetTexture(int kind);
	void SetTexture(ID3D11ShaderResourceView* texture);

	virtual void SetFloat(std::string key, float value){}
	virtual void SetFloat(std::string key, XMFLOAT4 value){}
	virtual void SetFloat(std::string key, XMFLOAT4X4 value){}

	MATERIAL& GetMaterial() {
		return *m_material;
	}
};

// EOF