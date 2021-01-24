#include "ShaderInfo.h"
#include "ShaderData.h"
#include "TextureData.h"

#define M_DIFFUSE		XMFLOAT4(1.0f,1.0f,1.0f,1.0f)
#define M_SPECULAR		XMFLOAT4(0.0f,0.0f,0.0f,1.0f)
#define M_AMBIENT		XMFLOAT4(0.0f,0.0f,0.0f,1.0f)
#define M_EMISSIVE		XMFLOAT4(0.0f,0.0f,0.0f,0.0f)

ShaderInfo::ShaderInfo(): m_VSKind(0), m_HSKind(-1), m_DSKind(-1), m_GSKind(-1),m_PSKind(0),m_material(nullptr), m_TexWorld(XMFLOAT4X4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)), m_pTexture(nullptr)
{
	m_material = new MATERIAL;
	// マテリアルの初期設定
	m_material->Diffuse = M_DIFFUSE;
	m_material->Ambient = M_AMBIENT;
	m_material->Specular = M_SPECULAR;
	m_material->Power = 0.0f;
	m_material->Emissive = M_EMISSIVE;
}

ShaderInfo::~ShaderInfo()
{
	delete m_material;
}

void ShaderInfo::SetShader()
{
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	ID3D11VertexShader* vs = ShaderData::GetVertexShader(m_VSKind);
	ID3D11HullShader*	hs = ShaderData::GetHullShader(m_HSKind);
	ID3D11GeometryShader* gs = ShaderData::GetGeometryShader(m_GSKind);
	ID3D11DomainShader* ds = ShaderData::GetDomainShader(m_DSKind);
	ID3D11PixelShader*	ps = ShaderData::GetPixelShader(m_PSKind);
	ID3D11InputLayout*	il = ShaderData::GetInputLayout(m_VSKind);

	// シェーダ設定
	pDeviceContext->VSSetShader(vs, nullptr, 0);
	pDeviceContext->HSSetShader(hs, nullptr, 0);
	pDeviceContext->DSSetShader(ds, nullptr, 0);
	pDeviceContext->GSSetShader(gs, nullptr, 0);
	pDeviceContext->PSSetShader(ps, nullptr, 0);
	pDeviceContext->IASetInputLayout(il);

}

ShaderInfo* ShaderInfo::ChangeColor(XMFLOAT3 color)
{
	m_material->Diffuse.x = color.x;
	m_material->Diffuse.y = color.y;
	m_material->Diffuse.z = color.z;

	return this;
}

ShaderInfo* ShaderInfo::ChangeColor(Vector3 color)
{
	m_material->Diffuse.x = color.x;
	m_material->Diffuse.y = color.y;
	m_material->Diffuse.z = color.z;

	return this;
}

ShaderInfo * ShaderInfo::ChangeColor(float r, float g, float b)
{
	m_material->Diffuse.x = r;
	m_material->Diffuse.y = g;
	m_material->Diffuse.z = b;

	return this;
}

ShaderInfo* ShaderInfo::ChangeColor(XMFLOAT4 color)
{
	m_material->Diffuse = color;

	return this;
}

ShaderInfo * ShaderInfo::ChangeColor(float r, float g, float b, float a)
{
	m_material->Diffuse.x = r;
	m_material->Diffuse.y = g;
	m_material->Diffuse.z = b;
	m_material->Diffuse.w = a;

	return this;
}

ShaderInfo* ShaderInfo::ChangeAlpha(float alpha)
{
	m_material->Diffuse.w = alpha;

	return this;
}

/**
* @brief テクスチャのセット
* @param[in] kind テクスチャの種類のenum番号
* @retrun なし
*/
ShaderInfo* ShaderInfo::SetTexture(int kind)
{
	m_pTexture = TextureData::GetInstance().GetData(kind);

	return this;
}

/**
* @brief テクスチャのセット
* @param[in] texture テクスチャデータ
* @retrun なし
*/
void ShaderInfo::SetTexture(ID3D11ShaderResourceView* texture)
{
	m_pTexture = texture;
}


// EOF

void ShaderBuffer::Bind(int kind, UINT slot, void * data)
{
	UpdateData(data);

	switch (kind)
	{
	case ShaderKind::VS:
		BindVS(slot);
		break;
	case ShaderKind::HS:
		BindHS(slot);
		break;
	case ShaderKind::DS:
		BindDS(slot);
		break;
	case ShaderKind::GS:
		BindGS(slot);
		break;
	case ShaderKind::PS:
		BindPS(slot);
		break;
	default:
		break;
	}
}

void ShaderBuffer::UpdateData(void * data)
{
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	//D3D11_MAPPED_SUBRESOURCE pData;
	//if (SUCCEEDED(pDeviceContext->Map(m_cbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData))) {
	//	memcpy_s(pData.pData, pData.RowPitch, (void*)&data, sizeof(data));
	//	pDeviceContext->Unmap(m_cbuffer, 0);
	//}

	pDeviceContext->UpdateSubresource(m_cbuffer, 0,nullptr, data,0,0);
}