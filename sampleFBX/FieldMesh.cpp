/**
 * @file FieldMesh
 * @brief 地面のメッシュクラス
 */
#include "FieldMesh.h"
#include "Texture.h"
#include <d3d11.h>
#include "Graphics.h"
#include "GameObject.h"
#include "CCamera.h"

#define	TEXTURE_FILENAME	L"data/texture/field000.jpg"	// 読み込むテクスチャファイル名

HRESULT FieldMesh::Init()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = CGraphics::GetDevice();

	Mesh::Init();

	int nNumBlockH = 15, nNumBlockV = 15;
	float fSizeBlockH = 80, fSizeBlockV = 80;
	//m_transform = &m_Parent->GetTransform();

	// テクスチャの読み込み
	hr = CreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FILENAME,		// ファイルの名前
		&m_pTexture);	// 読み込むメモリー

	static Transform trans;
	m_TexTransform = &trans;

	// 頂点数の設定
	this->m_nNumVertex = (nNumBlockH + 1) * (nNumBlockV + 1);

	// インデックス数の設定
	this->m_nNumIndex = (nNumBlockH + 1) * 2 * nNumBlockV + (nNumBlockV - 1) * 2;

	// 一時的な頂点配列の作成
	VERTEX_3D* pVertexWk = new VERTEX_3D[this->m_nNumVertex];

	// 頂点配列の中身を埋める
	VERTEX_3D* pVtx = pVertexWk;
#if 0
	const float texSizeX = 1.0f / nNumBlockH;
	const float texSizeZ = 1.0f / nNumBlockV;
#else
	const float texSizeX = 1.0f;
	const float texSizeZ = 1.0f;
#endif

	for (int nCntVtxZ = 0; nCntVtxZ < nNumBlockV + 1; ++nCntVtxZ) {
		const float ANGLE = XM_2PI / nNumBlockH;

		for (int nCntVtxX = 0; nCntVtxX < nNumBlockH + 1; ++nCntVtxX) {
			// 頂点座標の設定
			pVtx[nCntVtxZ * (nNumBlockH + 1) + nCntVtxX].vtx.x = -(nNumBlockH / 2.0f) * fSizeBlockH + nCntVtxX * fSizeBlockH;
			pVtx[nCntVtxZ * (nNumBlockH + 1) + nCntVtxX].vtx.y = 0.0f;
			pVtx[nCntVtxZ * (nNumBlockH + 1) + nCntVtxX].vtx.z = (nNumBlockV / 2.0f) * fSizeBlockV - nCntVtxZ * fSizeBlockV;

			// 法線の設定
			pVtx[nCntVtxZ * (nNumBlockH + 1) + nCntVtxX].nor = XMFLOAT3(0.0f, 1.0, 0.0f);

			// 反射光の設定
			pVtx[nCntVtxZ * (nNumBlockH + 1) + nCntVtxX].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[nCntVtxZ * (nNumBlockH + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
			pVtx[nCntVtxZ * (nNumBlockH + 1) + nCntVtxX].tex.y = texSizeZ * nCntVtxZ;
		}
	}

	// 一時的なインデックス配列生成
	int* pIndexWk = new int[this->m_nNumIndex];

	//インデックスバッファの中身を埋める
	int* pIdx = pIndexWk;

	int nCntIdx = 0;
	for (int nCntVtxZ = 0; nCntVtxZ < nNumBlockV; ++nCntVtxZ) {
		if (nCntVtxZ > 0) {
			// 縮退ポリゴンのためのダブりの設定
			pIdx[nCntIdx] = (nCntVtxZ + 1) * (nNumBlockH + 1);
			nCntIdx++;
		}

		for (int nCntVtxX = 0; nCntVtxX < nNumBlockH + 1; ++nCntVtxX) {
			pIdx[nCntIdx] = (nCntVtxZ + 1) * (nNumBlockH + 1) + nCntVtxX;
			nCntIdx++;
			pIdx[nCntIdx] = nCntVtxZ * (nNumBlockH + 1) + nCntVtxX;
			nCntIdx++;
		}

		if (nCntVtxZ < nNumBlockV - 1) {
			// 縮退ポリゴンのためのダブりの設定
			pIdx[nCntIdx] = nCntVtxZ * (nNumBlockH + 1) + nNumBlockH;
			nCntIdx++;
		}
	}

	hr = Mesh::MakeMeshVertex(pVertexWk, pIndexWk);

	// 一時配列の解放
	delete[] pIndexWk;
	delete[] pVertexWk;

	return E_NOTIMPL;
}

void FieldMesh::Draw()
{
	m_View = CCamera::Get()->GetView();
	m_Proj = CCamera::Get()->GetProj();
	Mesh::Draw();
}

// EOF