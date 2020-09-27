/**
 * @file UIMesh
 * @brief UI�̃��b�V���N���X
 */
#include "UIMesh.h"
#include "Graphics.h"
#include "Texture.h"
#include "GameObject.h"

#define	TEXTURE_FILENAME	L"data/texture/field000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

HRESULT UIMesh::Init()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = CGraphics::GetDevice();

	Mesh::Init();

	int nNumBlockH = 8, nNumBlockV = 8;
	float fSizeBlockH = 80, fSizeBlockV = 80;
	m_transform = &m_Parent->GetTransform();
	m_transform->position.z = 1;
	
	// �I�u�W�F�N�g�̒��_�z��𐶐�
	m_nNumVertex = 4;
	VERTEX_3D* pVertexWk = new VERTEX_3D[m_nNumVertex];

	// ���_�z��̒��g�𖄂߂�
	VERTEX_3D* pVtx = pVertexWk;

	// ���_���W�̐ݒ�
	pVtx[0].vtx = XMFLOAT3(-1.0f / 2, 1.0f / 2, 0.0f);
	pVtx[1].vtx = XMFLOAT3(1.0f / 2, 1.0f / 2, 0.0f);
	pVtx[2].vtx = XMFLOAT3(-1.0f / 2, -1.0f / 2, 0.0f);
	pVtx[3].vtx = XMFLOAT3(1.0f / 2, -1.0f / 2, 0.0f);

	// �@���̐ݒ�
	pVtx[0].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);

	// ���ˌ��̐ݒ�
	pVtx[0].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = XMFLOAT2(0.0f, 0.0f);
	pVtx[1].tex = XMFLOAT2(1.0f, 0.0f);
	pVtx[2].tex = XMFLOAT2(0.0f, 1.0f);
	pVtx[3].tex = XMFLOAT2(1.0f, 1.0f);

	// �C���f�b�N�X�z��𐶐�
	m_nNumIndex = 4;
	int* pIndexWk = new int[m_nNumIndex];

	// �C���f�b�N�X�z��̒��g�𖄂߂�
	pIndexWk[0] = 0;
	pIndexWk[1] = 1;
	pIndexWk[2] = 2;
	pIndexWk[3] = 3;

	// ���_�o�b�t�@����
	hr = MakeMeshVertex(pVertexWk, pIndexWk);

	// �ꎞ�z��̉��
	delete[] pIndexWk;
	delete[] pVertexWk;

	return E_NOTIMPL;
}

void UIMesh::Draw()
{
	XMStoreFloat4x4(&m_View, XMMatrixLookAtLH(XMVectorSet(0.0f, 0.0f, -10.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)));
	XMStoreFloat4x4(&m_Proj,
		XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f, 100.0f));

	Mesh::Draw();
}

// EOF