/**
 * @file Mesh
 * @brief メッシュクラス
 */
#include "Mesh.h"
#include "ShaderData.h"
#include "Graphics.h"
#include "MyMath.h"
#include "CCamera.h"
#include "Light.h"
#include "FbxModel.h"
#include "Shader.h"
#include "Texture.h"

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

#define M_DIFFUSE		XMFLOAT4(1.0f,1.0f,1.0f,1.0f)
#define M_SPECULAR		XMFLOAT4(0.0f,0.0f,0.0f,1.0f)
#define M_AMBIENT		XMFLOAT4(0.0f,0.0f,0.0f,1.0f)
#define M_EMISSIVE		XMFLOAT4(0.0f,0.0f,0.0f,0.0f)

Mesh::Mesh()
{
	m_transform = nullptr;
	m_material = nullptr;
	m_pVertexBuffer = nullptr;
	m_pIndexBuffer = nullptr;
	m_nNumVertex = 0;
	m_nNumIndex = 0;
	m_primitiveType = PT_UNDEFINED;
	m_TexTransform = nullptr;
	m_pTexture = nullptr;

	m_material = new MATERIAL();
	// マテリアルの初期設定
	m_material->Diffuse = M_DIFFUSE;
	m_material->Ambient = M_AMBIENT;
	m_material->Specular = M_SPECULAR;
	m_material->Power = 0.0f;
	m_material->Emissive = M_EMISSIVE;
}

Mesh::~Mesh()
{
	delete m_material;
}

/**
 * @brief 初期化処理
 * @return なし
 */
void Mesh::Awake()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = CGraphics::GetDevice();
	// 定数バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SHADER_GLOBAL);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = pDevice->CreateBuffer(&bd, nullptr, &m_pConstantBuffer[0]);
	if (FAILED(hr)) return;
	bd.ByteWidth = sizeof(SHADER_GLOBAL2);
	hr = pDevice->CreateBuffer(&bd, nullptr, &m_pConstantBuffer[1]);
	if (FAILED(hr)) return;
	m_View = CCamera::Get()->GetView();
	m_Proj = CCamera::Get()->GetProj();
}

void Mesh::Uninit()
{
	for (int i = 0; i < _countof(m_pConstantBuffer); ++i) {
		SAFE_RELEASE(m_pConstantBuffer[i]);
	}
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

void Mesh::Update()
{
}

/**
 * @brief 描画処理
 * @return なし
 */
void Mesh::Draw()
{	
	CGraphics::SetCullMode(CULLMODE_NONE);
	CGraphics::SetZWrite(true);
	CGraphics::SetBlendState(BS_ALPHABLEND);
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	ID3D11VertexShader* vs = ShaderData::GetVertexShader(ShaderData::VS_KIND::VS_VERTEX);
	ID3D11PixelShader* ps = ShaderData::GetPixelShader(ShaderData::PS_KIND::PS_PIXEL);
	ID3D11InputLayout* il = ShaderData::GetInputLayout(ShaderData::VS_KIND::VS_VERTEX);
	ID3D11SamplerState* pSamplerState = CGraphics::GetSamplerState();

	// シェーダ設定
	pDeviceContext->VSSetShader(vs, nullptr, 0);
	pDeviceContext->PSSetShader(ps, nullptr, 0);
	pDeviceContext->IASetInputLayout(il);

	// 頂点バッファをセット
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	// インデックスバッファをセット
	pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
	pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);
	
	XMFLOAT4X4 f4x4World, f4x4TexWorld;
	f4x4World = MyMath::StoreXMFloat4x4(*m_transform);

	f4x4TexWorld = MyMath::StoreXMFloat4x4(*m_TexTransform);
	SHADER_GLOBAL cb;
	XMMATRIX mtxWorld = XMLoadFloat4x4(&f4x4World);
	cb.mWVP = XMMatrixTranspose(mtxWorld *
		XMLoadFloat4x4(&m_View) * XMLoadFloat4x4(&m_Proj));
	cb.mW = XMMatrixTranspose(mtxWorld);
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&f4x4TexWorld));
	pDeviceContext->UpdateSubresource(m_pConstantBuffer[0], 0, nullptr, &cb, 0, 0);
	pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer[0]);
	SHADER_GLOBAL2 cb2;
	cb2.vEye = XMLoadFloat3(&CCamera::Get()->GetEye());
	CFbxLight* light = Light::Get();
	// とりあえずライト無し
	cb2.vLightDir = XMVectorSet(0,0,0, 0.f);
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
	pDeviceContext->UpdateSubresource(m_pConstantBuffer[1], 0, nullptr, &cb2, 0, 0);
	pDeviceContext->PSSetConstantBuffers(1, 1, &m_pConstantBuffer[1]);

	// プリミティブ形状をセット
	static const D3D11_PRIMITIVE_TOPOLOGY pt[] = {
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,	// 0なら三角形ストリップ
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
	};
	pDeviceContext->IASetPrimitiveTopology(pt[m_primitiveType]);

	// ポリゴンの描画
	pDeviceContext->DrawIndexed(m_nNumIndex, 0, 0);
}

HRESULT Mesh::MakeMeshVertex(VERTEX_3D vertexWk[], int indexWk[])
{
	ID3D11Device* pDevice = CGraphics::GetDevice();

	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(VERTEX_3D) * m_nNumVertex;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertexWk;
	HRESULT hr = pDevice->CreateBuffer(&vbd, &initData, &m_pVertexBuffer);
	if (FAILED(hr)) {
		return hr;
	}

	CD3D11_BUFFER_DESC ibd(m_nNumIndex * sizeof(int), D3D11_BIND_INDEX_BUFFER);
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = indexWk;
	hr = pDevice->CreateBuffer(&ibd, &initData, &m_pIndexBuffer);

	return hr;
}

Mesh* Mesh::ChangeColor(XMFLOAT3 color)
{
	m_material->Diffuse.x = color.x;
	m_material->Diffuse.y = color.y;
	m_material->Diffuse.z = color.z;

	return this;
}

Mesh* Mesh::ChangeColor(Vector3 color)
{
	m_material->Diffuse.x = color.x;
	m_material->Diffuse.y = color.y;
	m_material->Diffuse.z = color.z;

	return this;
}

Mesh * Mesh::ChangeColor(float r, float g, float b)
{
	m_material->Diffuse.x = r;
	m_material->Diffuse.y = g;
	m_material->Diffuse.z = b;

	return this;
}

Mesh* Mesh::ChangeColor(XMFLOAT4 color)
{
	m_material->Diffuse = color;

	return this;
}

Mesh * Mesh::ChangeColor(float r, float g, float b, float a)
{
	m_material->Diffuse.x = r;
	m_material->Diffuse.y = g;
	m_material->Diffuse.z = b;
	m_material->Diffuse.w = a;

	return this;
}

Mesh* Mesh::ChangeSize(XMFLOAT3 size)
{
	if (m_transform == nullptr) {
		return this;
	}

	m_transform->scale.x = size.x;
	m_transform->scale.y = size.y;
	m_transform->scale.z = size.z;

	return this;
}

Mesh * Mesh::ChangeSize(float x, float y, float z)
{
	if (m_transform == nullptr) {
		return this;
	}

	m_transform->scale.x = x;
	m_transform->scale.y = y;
	m_transform->scale.z = z;
	return this;
}

Mesh* Mesh::ChangePos(XMFLOAT3 pos)
{
	if (m_transform == nullptr) {
		return this;
	}

	m_transform->position.x = pos.x;
	m_transform->position.y = pos.y;
	m_transform->position.z = pos.z;

	return this;
}

Mesh* Mesh::ChangePos(float x, float y, float z)
{
	if (m_transform == nullptr) {
		return this;
	}

	m_transform->position.x = x;
	m_transform->position.y = y;
	m_transform->position.z = z;

	return this;
}

Mesh* Mesh::ChangeUV(XMFLOAT2 uv)
{
	if (m_TexTransform == nullptr) {
		return this;
	}

	m_TexTransform->position.x = uv.x;
	m_TexTransform->position.y = uv.y;

	return this;
}

Mesh * Mesh::ChangeUV(float u, float v)
{
	if (m_TexTransform == nullptr) {
		return this;
	}

	m_TexTransform->position.x = u;
	m_TexTransform->position.y = v;

	return this;
}

Mesh* Mesh::SetTexture(ID3D11ShaderResourceView* texture)
{
	m_pTexture = texture;

	return this;
}

// EOF