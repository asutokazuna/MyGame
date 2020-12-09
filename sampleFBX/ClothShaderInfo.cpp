#include "ClothShaderInfo.h"
#include "ShaderData.h"
#include "CCamera.h"
#include "FbxModel.h"
#include "Light.h"
#include "TextureData.h"

#define NUM_VSCONSTANT (1)
#define NUM_PSCONSTANT (1)

//*****************************************************************************
// シェーダに渡す値
struct SHADER_GLOBAL {
	XMMATRIX	mWVP;		// ワールド×ビュー×射影行列(転置行列)
	XMMATRIX	mW;			// ワールド行列(転置行列)
	XMMATRIX	mTex;		// テクスチャ行列(転置行列)
	XMFLOAT4	value;
};
struct SHADER_GLOBAL2 {
	XMVECTOR	vEye;		// 視点座標
							// 光源
	XMVECTOR	vLightDir;	// 光源方向
	XMVECTOR	vLa;		// 光源色(アンビエント)
	XMVECTOR	vLd;		// 光源色(ディフューズ)
	XMVECTOR	vLs;		// 光源色(スペキュラ)
							// マテリアル
	XMVECTOR	vAmbient;	// アンビエント色(+テクスチャ有無)
	XMVECTOR	vDiffuse;	// ディフューズ色
	XMVECTOR	vSpecular;	// スペキュラ色(+スペキュラ強度)
	XMVECTOR	vEmissive;	// エミッシブ色
	XMFLOAT4	value;
};

static float g_time;

ClothShaderInfo::ClothShaderInfo() :m_TexWorld(XMFLOAT4X4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)), m_pTexture(nullptr), m_fadethrosh(0)
{
	m_VSKind = ShaderData::VS_CLOTH;
	m_HSKind = ShaderData::HS_CLOTH;
	m_DSKind = ShaderData::DS_CLOTH;
	m_PSKind = ShaderData::PS_CLOTH;

	m_DomainConstant = new ID3D11Buffer*();
	m_PixelConstant = new ID3D11Buffer*();
	g_time = 0;
	m_power = 0;
}

ClothShaderInfo::~ClothShaderInfo()
{
	delete m_DomainConstant;
	delete m_PixelConstant;
}

void ClothShaderInfo::Awake()
{
	CreateConstantBuffer<SHADER_GLOBAL>(m_DomainConstant);
	CreateConstantBuffer<SHADER_GLOBAL2>(m_PixelConstant);
	m_View = CCamera::Get()->GetView();
	m_Proj = CCamera::Get()->GetProj();
	m_world = XMFLOAT4X4();
	m_power = 0.1f;
}

void ClothShaderInfo::Uninit()
{
	for (int i = 0; i < NUM_VSCONSTANT; ++i) {
		SAFE_RELEASE(m_DomainConstant[i]);
	}
	for (int i = 0; i < NUM_PSCONSTANT; ++i) {
		SAFE_RELEASE(m_PixelConstant[i]);
	}
}

void ClothShaderInfo::UpdateConstant()
{
	g_time += 0.01f;
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	ID3D11SamplerState* pSamplerState = CGraphics::GetSamplerState();

	SetShader();

	pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
	pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);

	XMFLOAT4X4 f4x4World, f4x4TexWorld;

	f4x4TexWorld = m_TexWorld;
	SHADER_GLOBAL cb;
	XMMATRIX mtxWorld = XMLoadFloat4x4(&m_world);
	cb.mWVP = XMMatrixTranspose(mtxWorld *
		XMLoadFloat4x4(&m_View) * XMLoadFloat4x4(&m_Proj));
	cb.mW = XMMatrixTranspose(mtxWorld);
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&f4x4TexWorld));
	cb.value.x = g_time;
	cb.value.y = m_power;
	pDeviceContext->UpdateSubresource(m_DomainConstant[0], 0, nullptr, &cb, 0, 0);
	pDeviceContext->DSSetConstantBuffers(0, 1, &m_DomainConstant[0]);
	SHADER_GLOBAL2 cb2;
	cb2.vEye = XMLoadFloat3(&CCamera::Get()->GetEye());
	CFbxLight* light = Light::Get();
	// とりあえずライト無し
	//cb2.vLightDir = XMLoadFloat3(&light->m_direction);
	cb2.vLightDir = XMVectorSet(0, 0, 1, 0.f);
	cb2.vLa = XMLoadFloat4(&light->m_ambient);
	cb2.vLd = XMLoadFloat4(&light->m_diffuse);
	cb2.vLs = XMLoadFloat4(&light->m_specular);
	cb2.value.x = m_fadethrosh;
	MATERIAL* pMaterial = m_material;
	if (!pMaterial) pMaterial = m_material;
	cb2.vDiffuse = XMLoadFloat4(&pMaterial->Diffuse);
	cb2.vAmbient = XMVectorSet(pMaterial->Ambient.x, pMaterial->Ambient.y, pMaterial->Ambient.z,
		(m_pTexture != nullptr) ? 1.f : 0.f);
	cb2.vSpecular = XMVectorSet(pMaterial->Specular.x, pMaterial->Specular.y, pMaterial->Specular.z, pMaterial->Power);
	cb2.vEmissive = XMLoadFloat4(&pMaterial->Emissive);
	pDeviceContext->UpdateSubresource(m_PixelConstant[0], 0, nullptr, &cb2, 0, 0);
	pDeviceContext->PSSetConstantBuffers(1, 1, &m_PixelConstant[0]);
}

void ClothShaderInfo::SetTexture(int kind)
{
	m_pTexture = TextureData::GetInstance().GetData(kind);
}

void ClothShaderInfo::SetTexture(ID3D11ShaderResourceView * texture)
{
	m_pTexture = texture;
}

void ClothShaderInfo::SetFloat(std::string key, float value)
{
	if (key == "Power") {
		m_power = value;
	}
	else if (key == "Fade") {
		m_fadethrosh = value;
	}
}

void ClothShaderInfo::SetFloat(std::string key, XMFLOAT4X4 value)
{
	if (key == "Proj") {
		m_Proj = value;
	}
	else if (key == "View") {
		m_View = value;
	}
	else if (key == "World") {
		m_world = value;
	}
}
