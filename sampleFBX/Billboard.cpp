/**
 * @file Billboard
 * @brief ビルボードクラス
 * @author Ariga
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
#include "DefaultShaderInfo.h"

/**
 * @brief 初期化処理
 * @return　なし
 */
void Billboard::Awake()
{	
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = CGraphics::GetDevice();

	m_transform = &m_Parent->GetTransform();
	m_Parent->SetCastShadow(false);
	m_Parent->SetReciveShadow(false);

	Mesh::Awake();

	static Transform trans;

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
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();

	XMFLOAT4X4 f4x4World, f4x4View, f4x4Temp;
	XMMATRIX mtxTemp = XMMatrixIdentity();
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

	XMMATRIX mtxWorld = mtxTemp;

	XMMATRIX

	mtxScale = XMMatrixScaling(m_transform->scale.x, m_transform->scale.y, m_transform->scale.z);
	mtxWorld = XMMatrixMultiply(mtxScale, mtxWorld);

	XMMATRIX
	// 移動を反映
	mtxTranslate = XMMatrixTranslation(m_transform->position.x, m_transform->position.y, m_transform->position.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	XMStoreFloat4x4(&f4x4World, mtxWorld);
	XMStoreFloat4x4(&f4x4Temp, mtxWorld);

	XMFLOAT4X4 view, proj;

	view = CCamera::Get()->GetView();
	proj = CCamera::Get()->GetProj();

	m_default->SetFloat("View", view);
	m_default->SetFloat("Proj", proj);
	m_default->SetFloat("World", f4x4World);

	if (m_shader != nullptr) {
		m_shader->SetFloat("View", view);
		m_shader->SetFloat("Proj", proj);
		m_shader->SetFloat("World", f4x4World);
	}

	Mesh::Draw();
}

// EOF