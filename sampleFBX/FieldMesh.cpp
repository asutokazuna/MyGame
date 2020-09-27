/**
 * @file FieldMesh
 * @brief �n�ʂ̃��b�V���N���X
 */
#include "FieldMesh.h"
#include "Texture.h"
#include <d3d11.h>
#include "Graphics.h"
#include "GameObject.h"
#include "CCamera.h"

#define	TEXTURE_FILENAME	L"data/texture/field000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

HRESULT FieldMesh::Init()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = CGraphics::GetDevice();

	Mesh::Init();

	int nNumBlockH = 15, nNumBlockV = 15;
	float fSizeBlockH = 80, fSizeBlockV = 80;
	//m_transform = &m_Parent->GetTransform();

	// �e�N�X�`���̓ǂݍ���
	hr = CreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&m_pTexture);	// �ǂݍ��ރ������[

	static Transform trans;
	m_TexTransform = &trans;

	// ���_���̐ݒ�
	this->m_nNumVertex = (nNumBlockH + 1) * (nNumBlockV + 1);

	// �C���f�b�N�X���̐ݒ�
	this->m_nNumIndex = (nNumBlockH + 1) * 2 * nNumBlockV + (nNumBlockV - 1) * 2;

	// �ꎞ�I�Ȓ��_�z��̍쐬
	VERTEX_3D* pVertexWk = new VERTEX_3D[this->m_nNumVertex];

	// ���_�z��̒��g�𖄂߂�
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
			// ���_���W�̐ݒ�
			pVtx[nCntVtxZ * (nNumBlockH + 1) + nCntVtxX].vtx.x = -(nNumBlockH / 2.0f) * fSizeBlockH + nCntVtxX * fSizeBlockH;
			pVtx[nCntVtxZ * (nNumBlockH + 1) + nCntVtxX].vtx.y = 0.0f;
			pVtx[nCntVtxZ * (nNumBlockH + 1) + nCntVtxX].vtx.z = (nNumBlockV / 2.0f) * fSizeBlockV - nCntVtxZ * fSizeBlockV;

			// �@���̐ݒ�
			pVtx[nCntVtxZ * (nNumBlockH + 1) + nCntVtxX].nor = XMFLOAT3(0.0f, 1.0, 0.0f);

			// ���ˌ��̐ݒ�
			pVtx[nCntVtxZ * (nNumBlockH + 1) + nCntVtxX].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[nCntVtxZ * (nNumBlockH + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
			pVtx[nCntVtxZ * (nNumBlockH + 1) + nCntVtxX].tex.y = texSizeZ * nCntVtxZ;
		}
	}

	// �ꎞ�I�ȃC���f�b�N�X�z�񐶐�
	int* pIndexWk = new int[this->m_nNumIndex];

	//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
	int* pIdx = pIndexWk;

	int nCntIdx = 0;
	for (int nCntVtxZ = 0; nCntVtxZ < nNumBlockV; ++nCntVtxZ) {
		if (nCntVtxZ > 0) {
			// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
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
			// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
			pIdx[nCntIdx] = nCntVtxZ * (nNumBlockH + 1) + nNumBlockH;
			nCntIdx++;
		}
	}

	hr = Mesh::MakeMeshVertex(pVertexWk, pIndexWk);

	// �ꎞ�z��̉��
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