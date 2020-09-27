/**
 * @file BulletTime.cpp
 * @breif �o���b�g�^�C�����H�J����
 */
#include "BulletTime.h"
#include "CPlayer.h"

// ��]���x�i�p���x�A���W�A���j
namespace {
	const float g_fRotateSpeed = 1;	// �P�ʁF�x
	const float g_fRadius = 156.0f;
}

HRESULT CBulletTime::Init()
{
	HRESULT hr = S_OK;
	m_vEye = XMFLOAT3(0.0f, 0.0f, -g_fRadius * 2.0f);
	m_vLook = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_vUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_fFOVY = XMConvertToRadians(45);
	m_fangle = 0.0f;
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fNearZ = 10.0f;
	m_fFarZ = 10000.0f;
	return hr;
}

void CBulletTime::Uninit()
{
	CCamera::Uninit();
}

void CBulletTime::Update()
{
	// �p�x�X�V
	m_fangle += g_fRotateSpeed;
	if (m_fangle >= 180) {
		m_fangle -= 360;
	}
	// ��]�}�g���b�N�X����
	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(m_fangle));
	// ���_���W����]
	XMStoreFloat3(&m_vEye,
	XMVector3TransformCoord(
	XMVectorSet(0.0f, 0.0f, -g_fRadius * 2,1.0f),mRotate));

	//// �v���C���[�ʒu�Ɉړ�
	//m_vLook = CPlayer::GetPos();
	//m_vEye.x += m_vLook.x;
	//m_vEye.y += m_vLook.y;
	//m_vEye.z += m_vLook.z;
	// �s��X�V
	CCamera::Update();
}

// EOF