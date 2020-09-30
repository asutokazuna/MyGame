/**
 * @file Billboard
 * @brief ビルボードクラス
 */
#include "Billboard.h"
#include "Texture.h"
#include <d3d11.h>
#include "Graphics.h"
#include "GameObject.h"
#include "CCamera.h"
#include "Mesh.h"
#include "ShaderData.h"
#include "FbxModel.h"
#include "Light.h"

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

/**
 * @brief 初期化処理
 * @return　なし
 */
void Billboard::Awake()
{	
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = CGraphics::GetDevice();

	Mesh::Awake();
	
	int nNumBlockH = 8, nNumBlockV = 8;
	float fSizeBlockH = 80, fSizeBlockV = 80;
	m_transform = &m_Parent->GetTransform();

	static Transform trans;
	m_TexTransform = &trans;

	// オブジェクトの頂点配列を生成
	m_nNumVertex = 4;
	VERTEX_3D* pVertexWk = new VERTEX_3D[m_nNumVertex];

	// 頂点配列の中身を埋める
	VERTEX_3D* pVtx = pVertexWk;

	// 頂点座標の設定
	pVtx[0].vtx = XMFLOAT3(-1.0f / 2, 1.0f / 2, 0.0f);
	pVtx[1].vtx = XMFLOAT3(1.0f / 2, 1.0f / 2, 0.0f);
	pVtx[2].vtx = XMFLOAT3(-1.0f / 2, -1.0f / 2, 0.0f);
	pVtx[3].vtx = XMFLOAT3(1.0f / 2, -1.0f / 2, 0.0f);

	// 法線の設定
	pVtx[0].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);

	// 反射光の設定
	pVtx[0].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = XMFLOAT2(0.0f, 0.0f);
	pVtx[1].tex = XMFLOAT2(1.0f, 0.0f);
	pVtx[2].tex = XMFLOAT2(0.0f, 1.0f);
	pVtx[3].tex = XMFLOAT2(1.0f, 1.0f);

	// インデックス配列を生成
	m_nNumIndex = 4;
	int* pIndexWk = new int[m_nNumIndex];

	// インデックス配列の中身を埋める
	pIndexWk[0] = 0;
	pIndexWk[1] = 1;
	pIndexWk[2] = 2;
	pIndexWk[3] = 3;

	// 頂点バッファ生成
	hr = MakeMeshVertex(pVertexWk, pIndexWk);

	// 一時配列の解放
	delete[] pIndexWk;
	delete[] pVertexWk;
}

/**
 * @brief 描画処理
 * @return なし
 */
void Billboard::Draw()
{
	//CGraphics::SetZWrite(false);
	m_Proj = CCamera::Get()->GetProj();
	m_View = CCamera::Get()->GetView();

	// 前面カリング (FBXは表裏が反転するため)
	CGraphics::SetCullMode(CULLMODE_NONE);
	CGraphics::SetZWrite(true);
	CGraphics::SetBlendState(BS_NONE);
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	ID3D11VertexShader* vs = ShaderData::GetVertexShader(ShaderData::VS_KIND::VS_VERTEX);
	ID3D11PixelShader* ps = ShaderData::GetPixelShader(ShaderData::PS_KIND::PS_PIXEL);
	ID3D11InputLayout* il = ShaderData::GetInputLayout(ShaderData::VS_KIND::VS_VERTEX);
	ID3D11SamplerState* pSamplerState = CGraphics::GetSamplerState();

	// あとでここもラッピングする
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

	//static Transform temp;
	//temp.scale.x = 100;
	//temp.scale.y = 100;
	//temp.scale.z = 100;

	XMFLOAT4X4 f4x4World, f4x4TexWorld, f4x4View, f4x4Temp;
	XMMATRIX mtxTemp = XMMatrixIdentity();;
	XMStoreFloat4x4(&f4x4Temp, mtxTemp);
	f4x4World = MyMath::StoreXMFloat4x4(*m_transform);

	f4x4View = CCamera::Get()->GetView();

	f4x4Temp._11 = f4x4View._11;
	f4x4Temp._12 = f4x4View._21;
	f4x4Temp._13 = f4x4View._31;
	f4x4Temp._21 = f4x4View._12;
	f4x4Temp._22 = f4x4View._22;
	f4x4Temp._23 = f4x4View._32;
	f4x4Temp._31 = f4x4View._13;
	f4x4Temp._32 = f4x4View._23;
	f4x4Temp._33 = f4x4View._33;

	mtxTemp = XMLoadFloat4x4(&f4x4Temp);

	f4x4TexWorld = MyMath::StoreXMFloat4x4(*m_TexTransform);
	SHADER_GLOBAL cb;
	XMMATRIX mtxWorld = mtxTemp;

	XMMATRIX

	mtxScale = XMMatrixScaling(m_transform->scale.x, m_transform->scale.y, m_transform->scale.z);
	mtxWorld = XMMatrixMultiply(mtxScale, mtxWorld);

	XMMATRIX
	// 移動を反映
	mtxTranslate = XMMatrixTranslation(m_transform->position.x, m_transform->position.y, m_transform->position.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);


	//mtxWorld = XMMatrixMultiply(mtxWorld, mtxTemp);

	cb.mWVP = XMMatrixTranspose(mtxWorld *
		XMLoadFloat4x4(&m_View) * XMLoadFloat4x4(&m_Proj));
	cb.mW = XMMatrixTranspose(mtxWorld);
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&f4x4TexWorld));
	pDeviceContext->UpdateSubresource(m_pConstantBuffer[0], 0, nullptr, &cb, 0, 0);
	pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer[0]);
	SHADER_GLOBAL2 cb2;
	cb2.vEye = XMLoadFloat3(&CCamera::Get()->GetEye());
	CFbxLight light = CFbxLight();
	cb2.vLightDir = XMVectorSet(0,0,0, 0.f);
	cb2.vLa = XMLoadFloat4(&light.m_ambient);
	cb2.vLd = XMLoadFloat4(&light.m_diffuse);
	cb2.vLs = XMLoadFloat4(&light.m_specular);
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
	// 前面カリング (FBXは表裏が反転するため)
	CGraphics::SetCullMode(CULLMODE_CW);

	CGraphics::SetZWrite(true);
}

// EOF