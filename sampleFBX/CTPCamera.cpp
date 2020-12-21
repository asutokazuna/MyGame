/**
 * @file CTPCamera.cpp
 * @brief 三人称カメラ
 */
#include "CTPCamera.h"
#include "CPlayer.h"
#include "MyMath.h"
#include "Transform.h"

// 定数
namespace {	// 空のnamespaceを付けるとこのcppだけのグローバル変数になる
	const XMFLOAT3 g_vEye(0.0f, 150.0f, -500.0f);
	const XMFLOAT3 g_vLook(0.0f, 120.0f, 0.0f);
	const XMFLOAT3 g_vUp(0.0f, 1.0f, 0.0f);
}

/**
 * @brief 初期化処理
 * @return なし
 */
void CTPCamera::Awake()
{
	HRESULT hr = S_OK;
	m_isActive = false;
	m_vEye = g_vEye;
	m_vLook = g_vLook;
	m_vUp = g_vUp;
	m_fFOVY = XMConvertToRadians(45);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fNearZ = 10.0f;
	m_fFarZ = 10000.0f;

	Transform* trs = this->transform;
	if (m_transform != nullptr) {
		trs = m_transform;
	}
	XMFLOAT4X4 mtxWorld = MyMath::StoreXMFloat4x4(*trs);

	// 始点と注視点を移動、上方ベクトルを回転
	XMMATRIX world = XMLoadFloat4x4(&mtxWorld);
	XMStoreFloat3(&m_vNowEye, XMVector3TransformCoord(XMLoadFloat3(&g_vEye), world));
	XMStoreFloat3(&m_vNowLook, XMVector3TransformCoord(XMLoadFloat3(&g_vLook), world));
	XMStoreFloat3(&m_vNowUp, XMVector3TransformNormal(XMLoadFloat3(&g_vUp), world));
	m_vEye = m_vNowEye;
	m_vLook = m_vNowLook;
	m_vUp = m_vNowUp;
	Update();
}

void CTPCamera::Uninit()
{
	CCamera::Uninit();
}

/**
 * @brief 更新処理
 * @return なし
 */
void CTPCamera::Update()
{
	Transform* trs = this->transform;
	if (m_transform != nullptr) {
		trs = m_transform;
	}
	XMFLOAT4X4 mtxWorld =
		MyMath::StoreXMFloat4x4(*trs);

	// 始点と注視点を移動、上方ベクトルを回転
	XMMATRIX world = XMLoadFloat4x4(&mtxWorld);
	XMStoreFloat3(&m_vEye , XMVector3TransformCoord (XMLoadFloat3(&g_vEye), world));
	XMStoreFloat3(&m_vLook, XMVector3TransformCoord (XMLoadFloat3(&g_vLook), world));
	XMStoreFloat3(&m_vUp  , XMVector3TransformNormal(XMLoadFloat3(&g_vUp), world));

	const float ratio = 0.92f;

	// 始点、注視点、上方ベクトルを近づける
	m_vNowEye.x = m_vNowEye.x   * ratio + m_vEye.x  * (1 - ratio);
	m_vNowEye.y = m_vNowEye.y   * ratio + m_vEye.y  * (1 - ratio);
	m_vNowEye.z = m_vNowEye.z   * ratio + m_vEye.z  * (1 - ratio);
	m_vNowLook.x = m_vNowLook.x * ratio + m_vLook.x * (1 - ratio);
	m_vNowLook.y = m_vNowLook.y * ratio + m_vLook.y * (1 - ratio);
	m_vNowLook.z = m_vNowLook.z * ratio + m_vLook.z * (1 - ratio);
	m_vNowUp.x = m_vNowUp.x     * ratio + m_vUp.x   * (1 - ratio);
	m_vNowUp.y = m_vNowUp.y     * ratio + m_vUp.y   * (1 - ratio);
	m_vNowUp.z = m_vNowUp.z     * ratio + m_vUp.z   * (1 - ratio);

	// 行列更新
	CCamera::Update();
}

// EOF