/**
 * @file BattleCamera.cpp
 * @brief 戦闘中のカメラ
 */
#include "BattleCamera.h"
#include "MyMath.h"

 // 定数
namespace {	// 空のnamespaceを付けるとこのcppだけのグローバル変数になる
	const XMFLOAT3 g_vEye(0.0f, 10.0f, -50.0f);
	const XMFLOAT3 g_vLook(0.0f, 120.0f, 0.0f);
	const XMFLOAT3 g_vUp(0.0f, 1.0f, 0.0f);
}

 /**
 * @brief 初期化処理
 * @return なし
 */
void BattleCamera::Awake()
{
	m_isActive = false;
	//m_vEye = g_vEye;
	//m_vLook = g_vLook;
	//m_vUp = g_vUp;
	m_fFOVY = MyMath::AngleToRadian(45);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fNearZ = 10.0f;
	m_fFarZ = 10000.0f;
	transform->position = Vector3(g_vEye.x, g_vEye.y, g_vEye.z);
}

HRESULT BattleCamera::Init()
{
	Transform* trs = this->transform;
	if (m_transform != nullptr) {
		trs = m_transform;
	}

	XMFLOAT4X4 mtxWorld = MyMath::StoreXMFloat4x4(*trs);
	// 始点と注視点を移動、上方ベクトルを回転
	XMMATRIX world = XMLoadFloat4x4(&mtxWorld);
	//XMStoreFloat3(&m_vNowEye, XMVector3TransformCoord(XMLoadFloat3(&g_vEye), world));
	//XMStoreFloat3(&m_vNowLook, XMVector3TransformCoord(XMLoadFloat3(&g_vLook), world));
	//XMStoreFloat3(&m_vNowUp, XMVector3TransformNormal(XMLoadFloat3(&g_vUp), world));
	//m_vEye = m_vNowEye;
	//m_vLook = m_vNowLook;
	//m_vUp = m_vNowUp;
	//Update();

	return S_OK;
}

void BattleCamera::Update()
{

	Transform* trs = this->transform;
	if (m_transform != nullptr) {
		trs = m_transform;
	}
	XMFLOAT4X4 mtxWorld =
		MyMath::StoreXMFloat4x4(*trs);

	// 始点と注視点を移動、上方ベクトルを回転
	XMMATRIX world = XMLoadFloat4x4(&mtxWorld);
	//XMStoreFloat3(&m_vEye, XMVector3TransformCoord(XMLoadFloat3(&g_vEye), world));
	//XMStoreFloat3(&m_vLook, XMVector3TransformCoord(XMLoadFloat3(&g_vLook), world));
	//XMStoreFloat3(&m_vUp, XMVector3TransformNormal(XMLoadFloat3(&g_vUp), world));

	// 行列更新
	CCamera::Update();
}

// EOF