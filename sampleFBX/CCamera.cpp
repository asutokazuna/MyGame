#include "CCamera.h"
#include "ImGui/imgui.h"
#include "MyMath.h"

// 静的メンバ
CCamera* CCamera::m_pCamera = nullptr;
const float NEARZ = 10.0f;
const float FAR_Z = 10000.0f;
//XMFLOAT3 CCamera::m_vNowEye;	//!< 現在の視点
//XMFLOAT3 CCamera::m_vNowLook;	//!< 現在の注視点
//XMFLOAT3 CCamera::m_vNowUp;		//!< 現在の上方ベクトル

/**
 * @brief 初期化処理
 * @return なし
 */
void CCamera::Awake()
{
	HRESULT hr = S_OK;
	m_vEye = XMFLOAT3(0.0f, 200.0f, -400.0f);
	m_vLook = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_vUp = XMFLOAT3(0.0f, 1.0f, 0.0f);

	m_fFOVY = XMConvertToRadians(45);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fNearZ = NEARZ;
	m_fFarZ = FAR_Z;

	m_vNowEye = m_vEye;
	m_vNowLook = m_vLook;
	m_vNowUp = m_vUp;
	transform->position = Vector3(m_vEye.x, m_vEye.y, m_vEye.z);
	Vector3 look = Vector3(m_vLook.x, m_vLook.y, m_vLook.z);
	transform->quaternion = MyMath::LookAt(transform->position, look);
	//Update();
}

/**
 * @brief 終了処理
 * @return なし
 */
void CCamera::Uninit()
{

}

/**
 * @brief 更新処理
 * @return なし
 */
void CCamera::Update()
{
	//if (this->m_isActive == false) {
	//	//return;
	//}

	//m_vNowEye.x  = m_vEye.x;
	//m_vNowEye.y  = m_vEye.y;
	//m_vNowEye.z  = m_vEye.z;
	//m_vNowLook.x = m_vLook.x;
	//m_vNowLook.y = m_vLook.y;
	//m_vNowLook.z = m_vLook.z;
	//m_vNowUp.x   = m_vUp.x;
	//m_vNowUp.y   = m_vUp.y;
	//m_vNowUp.z   = m_vUp.z;
	XMStoreFloat3(&m_vNowUp, XMVector3Normalize(XMLoadFloat3(&m_vNowUp)));
	// ビュー変換更新
	XMStoreFloat4x4(&m_View,
		XMMatrixLookAtLH(XMLoadFloat3(&m_vNowEye), XMLoadFloat3(&m_vNowLook), XMLoadFloat3(&m_vNowUp)));

	// 射影変換更新
	XMStoreFloat4x4(&m_Proj, XMMatrixPerspectiveFovLH(m_fFOVY, m_fAspect, m_fNearZ, m_fFarZ));
	transform->position = Vector3(m_vNowEye.x, m_vNowEye.y, m_vNowEye.z);
	Vector3 look = Vector3(m_vNowLook.x, m_vNowLook.y, m_vNowLook.z);
	transform->quaternion = MyMath::LookAt(transform->position, look);
}

/**
 * @brief 描画処理
 * @return なし
 */
void CCamera::Draw()
{
#ifdef _DEBUG
	ImGui::Begin("Camera");
	ImGui::SliderFloat("Pos x", &m_vNowEye.x,  -1000.0f, 500.0f);
	ImGui::SliderFloat("Pos y", &m_vNowEye.y,  -1000.0f, 500.0f);
	ImGui::SliderFloat("Pos z", &m_vNowEye.z,  -1000.0f, 500.0f);
	ImGui::SliderFloat("Look x", &m_vNowLook.x, -500.0f, 500.0f);
	ImGui::SliderFloat("Look y", &m_vNowLook.y, -500.0f, 500.0f);
	ImGui::SliderFloat("Look z", &m_vNowLook.z, -500.0f, 500.0f);
	ImGui::End();
#endif
}
void CCamera::SetPos(XMFLOAT3 eye){	m_vEye = eye; }
void CCamera::SetTransform(Transform& trans) { 
	m_transform = &trans;
}
XMFLOAT4X4& CCamera::GetView() { return m_View; }
XMFLOAT4X4& CCamera::GetProj() { return m_Proj; }
XMFLOAT3& CCamera::GetEye() { return m_vNowEye; }
XMFLOAT3& CCamera::GetLook() { return m_vNowLook; }

void CCamera::SetLook(XMFLOAT3 vLook) { m_vLook = vLook; }

void CCamera::Set(CCamera* pCamera) 
{
	if (m_pCamera != NULL) {
		m_pCamera->m_isActive = false;
	}
	m_pCamera = pCamera; 
	m_pCamera->m_isActive = true;
}

CCamera* CCamera::Get() { 
	return m_pCamera; 
}

// EOF