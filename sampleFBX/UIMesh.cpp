/**
 * @file UIMesh
 * @brief UIのメッシュクラス
 */
#include "UIMesh.h"
#include "Graphics.h"
#include "Texture.h"
#include "GameObject.h"

#define	TEXTURE_FILENAME	L"data/texture/field000.jpg"	// 読み込むテクスチャファイル名
 
 /**
  * @brief 初期化処理
  * @return なし
  */
void UIMesh::Awake()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = CGraphics::GetDevice();

	Mesh::Awake();

	int nNumBlockH = 8, nNumBlockV = 8;
	float fSizeBlockH = 80, fSizeBlockV = 80;
	m_transform = &m_Parent->GetTransform();
	m_transform->position.z = 1;
	
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
void UIMesh::Draw()
{
	XMStoreFloat4x4(&m_View, XMMatrixLookAtLH(XMVectorSet(0.0f, 0.0f, -10.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)));
	XMStoreFloat4x4(&m_Proj,
		XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f, 100.0f));

	Mesh::Draw();
}

// EOF