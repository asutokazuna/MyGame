#include "LifeGaugeShaderInfo.h"
#include "ShaderData.h"
#include "Graphics.h"
#include "MyMath.h"
#include "Transform.h"
#include "Mesh.h"
#include "FbxModel.h"
#include "Light.h"
#include "CCamera.h"
#include "GameObject.h"
#include "TextureData.h"

#define NUM_VSCONSTANT (1)
#define NUM_PSCONSTANT (1)

/**
 * @brief コンストラクタ
 */
LifeGaugeShaderInfo::LifeGaugeShaderInfo()
{
	m_VSKind = ShaderData::VS_VERTEX;
	m_PSKind = ShaderData::PS_LIFEGAUGE;
	m_cbufferManager.Create<SHADER_GLOBAL>("SHADER_GLOBAL");
	m_cbufferManager.Create<SHADER_GLOBAL2>("SHADER_GLOBAL2");
}

/**
 * @brief デストラクタ
 */
LifeGaugeShaderInfo::~LifeGaugeShaderInfo()
{
}

/**
 * @brief 初期化
 * @retrun なし
 */
void LifeGaugeShaderInfo::Awake()
{
	m_View = CCamera::Get()->GetView();
	m_Proj = CCamera::Get()->GetProj();
	m_world = XMFLOAT4X4();
	m_SizePer = 1;
}

/**
 * @brief 終了
 * @retrun なし
 */
void LifeGaugeShaderInfo::Uninit()
{
}

/**
 * @brief コンスタントバッファの更新
 * @retrun なし
 */
void LifeGaugeShaderInfo::UpdateConstant()
{

	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	ID3D11SamplerState* pSamplerState = CGraphics::GetSamplerState();

	SetShader();

	pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
	pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	SHADER_GLOBAL cb;
	XMMATRIX mtxWorld = XMLoadFloat4x4(&m_world);
	cb.mWVP = XMMatrixTranspose(mtxWorld *
		XMLoadFloat4x4(&m_View) * XMLoadFloat4x4(&m_Proj));
	cb.mW = XMMatrixTranspose(mtxWorld);
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&m_TexWorld));
	//m_SG.BindVS(0);

	SHADER_GLOBAL2 cb2;
	cb2.vEye = XMLoadFloat3(&CCamera::Get()->GetEye());
	CFbxLight* light = Light::Get();
	// とりあえずライト無し
	cb2.vLightDir = XMVectorSet(0, 0, 0, 0.f);
	cb2.vLa = XMLoadFloat4(&light->m_ambient);
	cb2.vLd = XMLoadFloat4(&light->m_diffuse);
	cb2.vLs = XMLoadFloat4(&light->m_specular);
	MATERIAL* pMaterial = m_material;
	if (!pMaterial) pMaterial = m_material;
	cb2.vDiffuse = XMLoadFloat4(&pMaterial->Diffuse);
	cb2.vAmbient = XMVectorSet(pMaterial->Ambient.x, pMaterial->Ambient.y, pMaterial->Ambient.z,
		(m_pTexture != nullptr) ? 1.f : 0.f);
	cb2.vSpecular = XMVectorSet(pMaterial->Specular.x, pMaterial->Specular.y, pMaterial->Specular.z, pMaterial->Power);
	cb2.vEmissive = XMLoadFloat4(&pMaterial->Emissive);
	cb2.value.x = m_SizePer;
	//m_SG2.BindPS(1);

	m_cbufferManager.BindBuffer("SHADER_GLOBAL", ShaderKind::VS, &cb, 0);
	m_cbufferManager.BindBuffer("SHADER_GLOBAL2", ShaderKind::PS, &cb2, 1);
}

void LifeGaugeShaderInfo::SetView(XMFLOAT4X4 view)
{
	m_View = view;
}

void LifeGaugeShaderInfo::SetProj(XMFLOAT4X4 proj)
{
	m_Proj = proj;
}

/**
 * @brief コンスタントバッファのデータをセット
 * @param[in] key 変数の判別するキー
 * @param[in] value セットする値
 * @retrun なし
 */
void LifeGaugeShaderInfo::SetFloat(std::string key, XMFLOAT4X4 value)
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
	else if ("TexWorld")
	{
		m_TexWorld = value;
	}
}

void LifeGaugeShaderInfo::SetFloat(std::string key, float value)
{
	if (key == "Life") {
		m_SizePer = value;
	}
}

/**
 * @brief UVの設定
 * @param[in] uv UV位置
 * @param[in] scale UVサイズ
 * @return なし
 */
void LifeGaugeShaderInfo::SetUV(Vector3 uv, Vector3 scale)
{
	XMMATRIX mtx = XMMatrixIdentity();

	mtx = XMMatrixScaling(scale.x, scale.y, scale.z);

	mtx *= XMMatrixTranslation(uv.x, uv.y, uv.z);

	XMStoreFloat4x4(&m_TexWorld, mtx);
}

// EOF