#include "CCamera.h"
#include "ImGui/imgui.h"

// 静的メンバ
CCamera* CCamera::m_pCamera = nullptr;
const float NEARZ = 10.0f;
const float FAR_Z = 10000.0f;
XMFLOAT3 CCamera::m_vNowEye;	//!< 現在の視点
XMFLOAT3 CCamera::m_vNowLook;	//!< 現在の注視点
XMFLOAT3 CCamera::m_vNowUp;		//!< 現在の上方ベクトル

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

HRESULT CCamera::Init()
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
	//Update();
	return hr;
}

void CCamera::Uninit()
{

}

void CCamera::Update()
{
	// 始点、注視点、上方ベクトルを近づける
	m_vNowEye.x = m_vNowEye.x * 0.5f + m_vEye.x * 0.5f;
	m_vNowEye.y = m_vNowEye.y * 0.5f + m_vEye.y * 0.5f;
	m_vNowEye.z = m_vNowEye.z * 0.5f + m_vEye.z * 0.5f;
	m_vNowLook.x = m_vNowLook.x * 0.5f + m_vLook.x * 0.5f;
	m_vNowLook.y = m_vNowLook.y * 0.5f + m_vLook.y * 0.5f;
	m_vNowLook.z = m_vNowLook.z * 0.5f + m_vLook.z * 0.5f;
	m_vNowUp.x = m_vNowUp.x * 0.5f + m_vUp.x * 0.5f;
	m_vNowUp.y = m_vNowUp.y * 0.5f + m_vUp.y * 0.5f;
	m_vNowUp.z = m_vNowUp.z * 0.5f + m_vUp.z * 0.5f;
	XMStoreFloat3(&m_vNowUp, XMVector3Normalize(XMLoadFloat3(&m_vNowUp)));
	// ビュー変換更新
	XMStoreFloat4x4(&m_View,
		XMMatrixLookAtLH(XMLoadFloat3(&m_vNowEye), XMLoadFloat3(&m_vNowLook), XMLoadFloat3(&m_vNowUp)));

	// 射影変換更新
	XMStoreFloat4x4(&m_Proj, XMMatrixPerspectiveFovLH(m_fFOVY, m_fAspect, m_fNearZ, m_fFarZ));
}

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
XMFLOAT3& CCamera::GetEye() { return m_vEye; }
XMFLOAT3& CCamera::GetLook() { return m_vLook; }

void CCamera::SetLook(XMFLOAT3 vLook) { m_vLook = vLook; }
void CCamera::Set(CCamera* pCamera) { m_pCamera = pCamera; }

CCamera* CCamera::Get() { 
	return m_pCamera; 
}

// EOF