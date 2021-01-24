#include "ClothShaderInfo.h"
#include "ShaderData.h"
#include "CCamera.h"
#include "FbxModel.h"
#include "Light.h"
#include "TextureData.h"

#define NUM_VSCONSTANT (1)
#define NUM_PSCONSTANT (1)

static float g_time;

/**
 * @brief コンストラクタ
 */
ClothShaderInfo::ClothShaderInfo() : m_fadethrosh(0), m_pNoizeTexture(nullptr)
{
	m_VSKind = ShaderData::VS_CLOTH;
	m_HSKind = ShaderData::HS_CLOTH;
	m_DSKind = ShaderData::DS_CLOTH;
	m_PSKind = ShaderData::PS_CLOTH;

	m_cbufferManager.Create<SHADER_GLOBAL>("SHADER_GLOBAL");
	m_cbufferManager.Create<SHADER_GLOBAL2>("SHADER_GLOBAL2");
	g_time = 0;
	m_power = 0;
}

ClothShaderInfo::~ClothShaderInfo()
{
}

void ClothShaderInfo::Awake()
{
	m_View = CCamera::Get()->GetView();
	m_Proj = CCamera::Get()->GetProj();
	m_world = XMFLOAT4X4();
	m_power = 0.1f;
}

void ClothShaderInfo::Uninit()
{
}

void ClothShaderInfo::UpdateConstant()
{
	//g_time += 0.01f;
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	ID3D11SamplerState* pSamplerState = CGraphics::GetSamplerState();

	SetShader();

	ID3D11ShaderResourceView* pTex[] = {
		m_pTexture,m_pNoizeTexture,
	};
	int texCount = _countof(pTex);
	pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
	pDeviceContext->PSSetShaderResources(0, texCount, pTex);

	XMFLOAT4X4 f4x4TexWorld;

	f4x4TexWorld = m_TexWorld;
	SHADER_GLOBAL cb;
	XMMATRIX mtxWorld = XMLoadFloat4x4(&m_world);
	cb.mWVP = XMMatrixTranspose(mtxWorld *
		XMLoadFloat4x4(&m_View) * XMLoadFloat4x4(&m_Proj));
	cb.mW = XMMatrixTranspose(mtxWorld);
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&f4x4TexWorld));
	cb.value.x = g_time;
	cb.value.y = 0;
	//m_SG.BindDS(0);
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
	//m_SG2.BindPS(1);
	m_cbufferManager.BindBuffer("SHADER_GLOBAL", ShaderKind::DS, &cb, 0);
	m_cbufferManager.BindBuffer("SHADER_GLOBAL2", ShaderKind::PS, &cb2, 1);
}

void ClothShaderInfo::SetNoizeTexture(int kind)
{
	m_pNoizeTexture = TextureData::GetInstance().GetData(kind);
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

// EOF