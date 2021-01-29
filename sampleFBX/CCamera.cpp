#include "CCamera.h"
#include "ImGui/imgui.h"
#include "MyMath.h"

// 静的メンバ
CCamera* CCamera::m_pCamera = nullptr;
CCamera* CCamera::m_pPreCamera = nullptr;

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

	transform->position = Vector3(0.0f, 200.0f, -400.0f);
	m_vLook = Vector3(0.0f, 0.0f, 0.0f);
	m_vUp = Vector3(0.0f, 1.0f, 0.0f);
	m_width = 10;
	m_height = 10;
	m_fFOVY = XMConvertToRadians(45);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fNearZ = NEARZ;
	m_fFarZ = FAR_Z;

	transform->quaternion = MyMath::LookAt(transform->position, m_vLook);
	UpdateMatrix();
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

}

/**
 * @brief 描画処理
 * @return なし
 */
void CCamera::Draw()
{
#ifdef _DEBUG
	if (ImGui::TreeNode("Camera")) {
		//ImGui::SliderFloat("Pos x", &m_vNowEye.x, -1000.0f, 500.0f);
		//ImGui::SliderFloat("Pos y", &m_vNowEye.y, -1000.0f, 500.0f);
		//ImGui::SliderFloat("Pos z", &m_vNowEye.z, -1000.0f, 500.0f);
		//ImGui::SliderFloat("Look x", &m_vNowLook.x, -500.0f, 500.0f);
		//ImGui::SliderFloat("Look y", &m_vNowLook.y, -500.0f, 500.0f);
		//ImGui::SliderFloat("Look z", &m_vNowLook.z, -500.0f, 500.0f);		
		Vector3 te2 = transform->position;
		ImGui::SliderFloat("Pos x", &te2.x, -1000.0f, 500.0f);
		ImGui::SliderFloat("Pos y", &te2.y, -1000.0f, 500.0f);
		ImGui::SliderFloat("Pos z", &te2.z, -1000.0f, 500.0f);
		ImGui::TreePop();
	}
#endif
}

void CCamera::UpdateMatrix()
{
	XMFLOAT3 pos;
	XMFLOAT3 look;
	XMFLOAT3 up;
	
	Vector3 cameraPos = transform->position;
	Vector3 cameraUP = transform->GetUp();

	pos = XMFLOAT3(cameraPos.x, cameraPos.y, cameraPos.z);
	look = XMFLOAT3(m_vLook.x, m_vLook.y, m_vLook.z);
	up = XMFLOAT3(m_vUp.x, m_vUp.y, m_vUp.z);

	// ビュー変換更新
	XMStoreFloat4x4(&m_View,
		XMMatrixLookAtLH(XMLoadFloat3(&pos), XMLoadFloat3(&look), XMLoadFloat3(&up)));

	// 射影変換更新
	XMStoreFloat4x4(&m_Proj, XMMatrixPerspectiveFovLH(m_fFOVY, m_fAspect, m_fNearZ, m_fFarZ));
}


void CCamera::UpdateMatrixOrthograph()
{
	XMFLOAT3 pos;
	XMFLOAT3 look;
	XMFLOAT3 up;

	Vector3 cameraPos = transform->position;
	Vector3 cameraUP = transform->GetUp();

	pos = XMFLOAT3(cameraPos.x, cameraPos.y, cameraPos.z);
	look = XMFLOAT3(m_vLook.x, m_vLook.y, m_vLook.z);
	up = XMFLOAT3(m_vUp.x, m_vUp.y, m_vUp.z);

	// ビュー変換更新
	XMStoreFloat4x4(&m_View,
		XMMatrixLookAtLH(XMLoadFloat3(&pos), XMLoadFloat3(&look), XMLoadFloat3(&up)));

	// 射影変換更新
	XMStoreFloat4x4(&m_Proj, XMMatrixOrthographicLH(m_width, m_height, m_fNearZ, m_fFarZ));
}

void CCamera::SetPos(XMFLOAT3 eye){	}
void CCamera::SetTransform(Transform& trans) { 
	m_transform = &trans;
}
XMFLOAT4X4& CCamera::GetView() { return m_View; }
XMFLOAT4X4& CCamera::GetProj() { return m_Proj; }
XMFLOAT3 CCamera::GetEye() { return XMFLOAT3(transform->position.x, transform->position.y, transform->position.z); }
//XMFLOAT3& CCamera::GetLook() { return m_vNowLook; }
//
//void CCamera::SetLook(XMFLOAT3 vLook) { m_vLook = vLook; }

void CCamera::Set(CCamera* pCamera) 
{
	if (m_pCamera != NULL) {
		m_pCamera->m_isActive = false;
	}
	m_pPreCamera = m_pCamera;
	m_pCamera = pCamera; 
	m_pCamera->m_isActive = true;
}

CCamera* CCamera::Get() { 
	return m_pCamera; 
}

// EOF