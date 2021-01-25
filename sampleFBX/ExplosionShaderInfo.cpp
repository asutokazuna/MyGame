#include "ExplosionShaderInfo.h"
#include "ShaderData.h"
#include "CCamera.h"
#include "Light.h"
#include "FbxModel.h"
#include "TextureData.h"

/**
 * @brief コンストラクタ
 */
ExplosionShaderInfo::ExplosionShaderInfo(): m_fadethrosh(0), m_pNoizeTexture(nullptr)
{
	m_VSKind = ShaderData::VS_DEFAULT;
	m_HSKind = ShaderData::HS_DEFAULT;
	m_DSKind = ShaderData::DS_DEFAULT;
	m_GSKind = ShaderData::GS_EXPLOSION;
	m_PSKind = ShaderData::PS_EXPLOSION;

	m_cbufferManager.Create<SHADER_GLOBAL>("SHADER_GLOBAL");
	m_cbufferManager.Create<SHADER_GLOBAL2>("SHADER_GLOBAL2");
	m_cbufferManager.Create<HULL_DATA>("HULL_DATA");
	m_time = 0;
	m_power = 0;
}

/**
 * @brief デストラクタ
 */
ExplosionShaderInfo::~ExplosionShaderInfo()
{
}

/**
 * @brief 初期化処理
 * @return なし
 */
void ExplosionShaderInfo::Awake()
{
	m_View = CCamera::Get()->GetView();
	m_Proj = CCamera::Get()->GetProj();
	m_world = XMFLOAT4X4();
	m_power = 0.1f;
	m_time = 0;
}

/**
 * @brief 終了処理
 * @return なし
 */
void ExplosionShaderInfo::Uninit()
{
}

/**
 * @brief 描画処理
 * @return なし
 */
void ExplosionShaderInfo::Draw()
{
#ifdef _DEBUG

	if (ImGui::TreeNode("Explosion")) {
		ImGui::SliderFloat("Dist", &m_power, 0, 1);
		ImGui::SliderFloat("fade", &m_fadethrosh, 0, 1);
		ImGui::TreePop();
	}
#endif
}

/**
 * @brief コンスタントバッファの更新
 * @return なし
 */
void ExplosionShaderInfo::UpdateConstant()
{
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	ID3D11SamplerState* pSamplerState = CGraphics::GetSamplerState();

	SetShader();

	ID3D11ShaderResourceView* pTex[] = {
		m_pTexture,m_pNoizeTexture
	};
	int texCount = _countof(pTex);
	pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
	pDeviceContext->PSSetShaderResources(0, texCount, pTex);

	HULL_DATA hullcb;
	hullcb.factor.x = 20;
	hullcb.factor.y = 20;
	hullcb.factor.z = 20;
	hullcb.factor.w = 20;
//	m_HD.BindHS(0);

	SHADER_GLOBAL cb;
	XMMATRIX mtxWorld = XMLoadFloat4x4(&m_world);
	cb.mWVP = XMMatrixTranspose(mtxWorld *
		XMLoadFloat4x4(&m_View) * XMLoadFloat4x4(&m_Proj));
	cb.mW = XMMatrixTranspose(mtxWorld);
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&m_TexWorld));
	cb.value.x = m_time;
	cb.value.y = m_power;
	//m_SG.BindGS(0);
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

	m_cbufferManager.BindBuffer("HULL_DATA", ShaderKind::HS, &hullcb, 0);
	m_cbufferManager.BindBuffer("SHADER_GLOBAL", ShaderKind::GS, &cb, 0);
	m_cbufferManager.BindBuffer("SHADER_GLOBAL2", ShaderKind::PS, &cb2, 1);
}

/**
 * @brief ノイズテクスチャのセット
 * @param[in] kind テクスチャの種類のenum番号
 * @retrun なし
 */
void ExplosionShaderInfo::SetNoizeTexture(int kind)
{
	m_pNoizeTexture = TextureData::GetInstance().GetData(kind);
}

/**
 * @brief コンスタントバッファのデータをセット
 * @param[in] key 変数の判別するキー
 * @param[in] value セットする値
 * @retrun なし
 */
void ExplosionShaderInfo::SetFloat(std::string key, float value)
{
	if (key == "Power") {
		m_power = value;
	}
	else if (key == "Fade") {
		m_fadethrosh = value;
	}
}

/**
 * @brief コンスタントバッファのデータをセット
 * @param[in] key 変数の判別するキー
 * @param[in] value セットする値
 * @retrun なし
 */
void ExplosionShaderInfo::SetFloat(std::string key, XMFLOAT4X4 value)
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