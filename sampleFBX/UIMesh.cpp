/**
 * @file UIMesh
 * @brief UIのメッシュクラス
 */
#include "UIMesh.h"
#include "Graphics.h"
#include "Texture.h"
#include "GameObject.h"
#include "DefaultShaderInfo.h"
 
 /**
  * @brief 初期化処理
  * @return なし
  */
void UIMesh::Awake()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = CGraphics::GetDevice();

	m_transform = &m_Parent->GetTransform();
	m_transform->position.z = 1;

	Mesh::Awake();

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

HRESULT UIMesh::Init()
{
	XMFLOAT4X4 view, proj, world;

	XMStoreFloat4x4(&view, XMMatrixLookAtLH(XMVectorSet(0.0f, 0.0f, -10.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)));
	XMStoreFloat4x4(&proj,
		XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f, 100.0f));
	world = MyMath::StoreXMFloat4x4(*m_transform);

	m_default->SetView(view);
	m_default->SetProj(proj);
	m_default->SetFloat("World", world);

	if (m_shader != nullptr) {
		m_shader->SetFloat("View",view);
		m_shader->SetFloat("Proj",proj);
	}
	return S_OK;
}

/**
 * @brief 描画処理
 * @return なし
 */
void UIMesh::Draw()
{
	XMFLOAT4X4 world;
	world = MyMath::StoreXMFloat4x4(*m_transform);

	if (m_shader != nullptr) {
		//m_shader->SetView(view);
		//m_shader->SetProj(proj
		m_shader->SetFloat("World", world);
	}

	Mesh::Draw();
}

// EOF