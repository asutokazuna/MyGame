#include "ExplosionShaderInfo.h"
#include "ShaderData.h"
#include "CCamera.h"
#include "Light.h"
#include "FbxModel.h"
#include "TextureData.h"

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
struct HULL_DATA
{
	XMFLOAT4 factor;
};

/**
 * @brief コンストラクタ
 */
ExplosionShaderInfo::ExplosionShaderInfo():m_TexWorld(XMFLOAT4X4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)), m_pTexture(nullptr), m_fadethrosh(0), m_pNoizeTexture(nullptr)
{
	m_VSKind = ShaderData::VS_DEFAULT;
	m_HSKind = ShaderData::HS_DEFAULT;
	m_DSKind = ShaderData::DS_DEFAULT;
	m_GSKind = ShaderData::GS_EXPLOSION;
	m_PSKind = ShaderData::PS_EXPLOSION;

	m_HullConstant = new ID3D11Buffer*();
	m_GeometryConstant = new ID3D11Buffer*();
	m_PixelConstant = new ID3D11Buffer*();
	m_time = 0;
	m_power = 0;
}

/**
 * @brief デストラクタ
 */
ExplosionShaderInfo::~ExplosionShaderInfo()
{
	delete m_HullConstant;
	delete m_GeometryConstant;
	delete m_PixelConstant;
}

/**
 * @brief 初期化処理
 * @return なし
 */
void ExplosionShaderInfo::Awake()
{
	CreateConstantBuffer<SHADER_GLOBAL>(m_GeometryConstant);
	CreateConstantBuffer<SHADER_GLOBAL2>(m_PixelConstant);
	CreateConstantBuffer<HULL_DATA>(m_HullConstant);
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
	for (int i = 0; i < 1; ++i) {
		SAFE_RELEASE(m_HullConstant[i]);
	}
	for (int i = 0; i < 1; ++i) {
		SAFE_RELEASE(m_PixelConstant[i]);
	}
	for (int i = 0; i < 1; ++i) {
		SAFE_RELEASE(m_GeometryConstant[i]);
	}
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
	pDeviceContext->UpdateSubresource(m_HullConstant[0], 0, nullptr, &hullcb, 0, 0);
	pDeviceContext->HSSetConstantBuffers(0, 1, &m_HullConstant[0]);

	SHADER_GLOBAL cb;
	XMMATRIX mtxWorld = XMLoadFloat4x4(&m_world);
	cb.mWVP = XMMatrixTranspose(mtxWorld *
		XMLoadFloat4x4(&m_View) * XMLoadFloat4x4(&m_Proj));
	cb.mW = XMMatrixTranspose(mtxWorld);
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&m_TexWorld));
	cb.value.x = m_time;
	cb.value.y = m_power;
	pDeviceContext->UpdateSubresource(m_GeometryConstant[0], 0, nullptr, &cb, 0, 0);
	pDeviceContext->GSSetConstantBuffers(0, 1, &m_GeometryConstant[0]);
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

/**
 * @brief テクスチャのセット
 * @param[in] kind テクスチャの種類のenum番号
 * @retrun なし
 */
void ExplosionShaderInfo::SetTexture(int kind)
{
	m_pTexture = TextureData::GetInstance().GetData(kind);
}

/**
 * @brief テクスチャのセット
 * @param[in] texture テクスチャデータ
 * @retrun なし
 */
void ExplosionShaderInfo::SetTexture(ID3D11ShaderResourceView * texture)
{
	m_pTexture = texture;
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