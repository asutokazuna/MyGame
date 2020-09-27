/**
 * @file BulletTime.cpp
 * @breif バレットタイム風？カメラ
 */
#include "BulletTime.h"
#include "CPlayer.h"

// 回転速度（角速度、ラジアン）
namespace {
	const float g_fRotateSpeed = 1;	// 単位：度
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
	// 角度更新
	m_fangle += g_fRotateSpeed;
	if (m_fangle >= 180) {
		m_fangle -= 360;
	}
	// 回転マトリックス生成
	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(m_fangle));
	// 視点座標を回転
	XMStoreFloat3(&m_vEye,
	XMVector3TransformCoord(
	XMVectorSet(0.0f, 0.0f, -g_fRadius * 2,1.0f),mRotate));

	//// プレイヤー位置に移動
	//m_vLook = CPlayer::GetPos();
	//m_vEye.x += m_vLook.x;
	//m_vEye.y += m_vLook.y;
	//m_vEye.z += m_vLook.z;
	// 行列更新
	CCamera::Update();
}

// EOF