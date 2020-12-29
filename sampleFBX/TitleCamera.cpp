#include "TitleCamera.h"
// 定数
namespace {	// 空のnamespaceを付けるとこのcppだけのグローバル変数になる
	const XMFLOAT3 g_vEye(0.0f, 0.0f, -1.0f);
	const XMFLOAT3 g_vLook(10.0f, 1.0f, 0.0f);
	const XMFLOAT3 g_vUp(0.0f, 1.0f, 0.0f);
}

static float radian = 0;

void TitleCamera::Awake()
{
	HRESULT hr = S_OK;
	m_isActive = false;
	m_vEye = g_vEye;
	m_vLook = g_vLook;
	m_vUp = g_vUp;
	m_fFOVY = XMConvertToRadians(60);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fNearZ = 10.0f;
	m_fFarZ = 10000.0f;

	this->transform->position = Vector3(0,0,0);
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
	radian = 0;
}

/**
 * 定円
 * 動円
 * 描画円
 * 角度
 */
Vector3 Calctrochoid(float r1, float r2, float r3, float rad)
{
	Vector3 pos = Vector3();

	pos.x = (r1 - r2) * cosf(rad) + r3 * cosf((r1 - r2) / r2 * rad);
	pos.y = (r1 - r2) * sinf(rad) + r3 * sinf((r1 - r2) / r2 * rad);

	return pos;
}

Vector3 Calcgaitrochoid(float r1, float r2, float r3, float rad)
{
	Vector3 pos = Vector3();

	pos.x = (r1 + r2) * cosf(rad) - r3 * cosf((r1 + r2) / r2 * rad);
	pos.y = (r1 + r2) * sinf(rad) - r3 * sinf((r1 + r2) / r2 * rad);

	return pos;
}



void TitleCamera::Uninit()
{
	CCamera::Uninit();
}

void TitleCamera::Update()
{
	radian += 0.001f;
	Transform* trs = this->transform;
	if (m_transform != nullptr) {
		trs = m_transform;
	}
	Vector3 pos = Calcgaitrochoid(20, 80, 30, radian);

	trs->position.x = pos.x ;
	trs->position.z = pos.y ;

	//trs->rotation.x = pos.x ;
	//trs->rotation.z = pos.z ;
	XMFLOAT4X4 mtxWorld =
		MyMath::StoreXMFloat4x4(*trs);

	Vector3 lookpos = Calcgaitrochoid(60, 20, 20, radian);
	XMFLOAT4X4 f4f4mtx = XMFLOAT4X4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	f4f4mtx._41 = -lookpos.x;
	f4f4mtx._43 = lookpos.y;
	trs->position.x += lookpos.x;
	trs->position.y = lookpos.y / 10;
	// 始点と注視点を移動、上方ベクトルを回転
	XMMATRIX world = XMLoadFloat4x4(&mtxWorld);
	XMMATRIX lookworld = XMLoadFloat4x4(&f4f4mtx);
	//XMStoreFloat3(&m_vEye , XMVector3TransformCoord (XMLoadFloat3(&g_vEye), world));
	XMStoreFloat3(&m_vLook, XMVector3TransformCoord (XMLoadFloat3(&g_vLook), lookworld));
	XMStoreFloat3(&m_vUp  , XMVector3TransformNormal(XMLoadFloat3(&g_vUp), world));

	// 行列更新
	CCamera::Update();
}

// EOF