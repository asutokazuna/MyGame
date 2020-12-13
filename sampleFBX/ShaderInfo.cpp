#include "ShaderInfo.h"
#include "ShaderData.h"

#define M_DIFFUSE		XMFLOAT4(1.0f,1.0f,1.0f,1.0f)
#define M_SPECULAR		XMFLOAT4(0.0f,0.0f,0.0f,1.0f)
#define M_AMBIENT		XMFLOAT4(0.0f,0.0f,0.0f,1.0f)
#define M_EMISSIVE		XMFLOAT4(0.0f,0.0f,0.0f,0.0f)

ShaderInfo::ShaderInfo(): m_VSKind(0), m_HSKind(-1), m_DSKind(-1), m_GSKind(-1),m_PSKind(0),m_VertexConstant(nullptr), m_PixelConstant(nullptr), m_material(nullptr), m_DomainConstant(nullptr)
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


// EOF