/**
 * @file CTPCamera.cpp
 * @brief 三人称カメラ
 */
#include "CFPCamera.h"
#include "CPlayer.h"
#include "MyMath.h"
#include "Transform.h"

// 定数
namespace {	// 空のnamespaceを付けるとこのcppだけのグローバル変数になる
	const XMFLOAT3 g_vEye(0.0f, 14.0f, 24.0f);
	const XMFLOAT3 g_vLook(0.0f, 14.0f, 124.0f);
	const XMFLOAT3 g_vUp(0.0f, 1.0f, 0.0f);
}

HRESULT CFPCamera::Init()
{
	HRESULT hr = S_OK;
	m_vEye = g_vEye;
	m_vLook = g_vLook;
	m_vUp = g_vUp;
	m_fFOVY = XMConvertToRadians(45);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fNearZ = 10.0f;
	m_fFarZ = 10000.0f;
	Update();
	return hr;
}

void CFPCamera::Uninit()
{
	CCamera::Uninit();
}

void CFPCamera::Update()
{
	XMFLOAT4X4 mtxWorld = 
	MyMath::StoreXMFloat4x4(*m_transform);

	// 始点と注視点を移動、上方ベクトルを回転
	XMMATRIX world = XMLoadFloat4x4(&mtxWorld);
	XMStoreFloat3(&m_vEye , XMVector3TransformCoord (XMLoadFloat3(&g_vEye), world));
	XMStoreFloat3(&m_vLook, XMVector3TransformCoord (XMLoadFloat3(&g_vLook), world));
	XMStoreFloat3(&m_vUp  , XMVector3TransformNormal(XMLoadFloat3(&g_vUp), world));

	m_vNowEye = m_vEye;

	// 行列更新
	CCamera::Update();
}

// EOF