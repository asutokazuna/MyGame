#include "DefaultShaderInfo.h"
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

//*****************************************************************************
// シェーダに渡す値
struct SHADER_GLOBAL {
	XMMATRIX	mWVP;		// ワールド×ビュー×射影行列(転置行列)
	XMMATRIX	mW;			// ワールド行列(転置行列)
	XMMATRIX	mTex;		// テクスチャ行列(転置行列)
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
};

DefaultShaderInfo::DefaultShaderInfo():m_TexTransform(nullptr), m_pTexture(nullptr)
{
	m_VertexConstant = new ID3D11Buffer*();
	m_PixelConstant = new ID3D11Buffer*();
}

DefaultShaderInfo::~DefaultShaderInfo()
{
	delete m_VertexConstant;
	delete m_PixelConstant;
}

void DefaultShaderInfo::Awake()
{
	//CreateConstantBuffer<SHADER_GLOBAL>(m_VertexConstant);
	CreateConstantBuffer<SHADER_GLOBAL2>(&m_PixelConstant[0]);
	ID3D11Device* pDevice = CGraphics::GetDevice();
	// 定数バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SHADER_GLOBAL);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	pDevice->CreateBuffer(&bd, nullptr, m_VertexConstant);
	m_View = CCamera::Get()->GetView();
	m_Proj = CCamera::Get()->GetProj();
	m_world = XMFLOAT4X4();
}

void DefaultShaderInfo::Uninit()
{
	for (int i = 0; i < NUM_VSCONSTANT; ++i) {
		SAFE_RELEASE(m_VertexConstant[i]);
	}	
	for (int i = 0; i < NUM_PSCONSTANT; ++i) {
		SAFE_RELEASE(m_PixelConstant[i]);
	}
}

void DefaultShaderInfo::Draw()
{

	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	ID3D11SamplerState* pSamplerState = CGraphics::GetSamplerState();

	SetShader();

	pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
	pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	static Transform trans;
	trans.scale = Vector3(200, 200, 0);

	XMFLOAT4X4 f4x4World, f4x4TexWorld;

	f4x4TexWorld = MyMath::StoreXMFloat4x4(*m_TexTransform);
	SHADER_GLOBAL cb;
	XMMATRIX mtxWorld = XMLoadFloat4x4(&m_world);
	cb.mWVP = XMMatrixTranspose(mtxWorld *
		XMLoadFloat4x4(&m_View) * XMLoadFloat4x4(&m_Proj));
	cb.mW = XMMatrixTranspose(mtxWorld);
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&f4x4TexWorld));
	pDeviceContext->UpdateSubresource(m_VertexConstant[0], 0, nullptr, &cb, 0, 0);
	pDeviceContext->VSSetConstantBuffers(0, 1, &m_VertexConstant[0]);
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
	pDeviceContext->UpdateSubresource(m_PixelConstant[0], 0, nullptr, &cb2, 0, 0);
	pDeviceContext->PSSetConstantBuffers(1, 1, &m_PixelConstant[0]);
}


void DefaultShaderInfo::SetTexture(int kind)
{
	m_pTexture = TextureData::GetInstance().GetData(kind);
}

void DefaultShaderInfo::SetTexture(ID3D11ShaderResourceView* texture)
{
	m_pTexture = texture;
}

void DefaultShaderInfo::SetView(XMFLOAT4X4 view)
{
	m_View = view;
}

void DefaultShaderInfo::SetProj(XMFLOAT4X4 proj)
{
	m_Proj = proj;
}

void DefaultShaderInfo::SetFloat(std::string key, XMFLOAT4X4 value)
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