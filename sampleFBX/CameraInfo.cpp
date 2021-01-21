#include "CameraInfo.h"

#include "CameraInfo.h"
#include "ImGui/imgui.h"
#include "MyMath.h"
#include "GameObject.h"


// 静的メンバ
const float NEARZ = 10.0f;
const float FAR_Z = 10000.0f;
//XMFLOAT3 CameraInfo::m_vNowEye;	//!< 現在の視点
//XMFLOAT3 CameraInfo::m_vNowLook;	//!< 現在の注視点
//XMFLOAT3 CameraInfo::m_vNowUp;		//!< 現在の上方ベクトル

/**
* @brief 初期化処理
* @return なし
*/
void CameraInfo::Awake()
{
	HRESULT hr = S_OK;

	m_Parent->GetTransform().position = Vector3(0.0f, 200.0f, -400.0f);
	m_vLook = Vector3(0.0f, 0.0f, 0.0f);
	m_vUp = Vector3(0.0f, 1.0f, 0.0f);

	m_fFOVY = XMConvertToRadians(45);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fNearZ = NEARZ;
	m_fFarZ = FAR_Z;

	m_Parent->GetTransform().quaternion = MyMath::LookAt(m_Parent->GetTransform().position, m_vLook);
	UpdateMatrix();
}

/**
* @brief 終了処理
* @return なし
*/
void CameraInfo::Uninit()
{

}

/**
* @brief 更新処理
* @return なし
*/
void CameraInfo::Update()
{

}

/**
* @brief 描画処理
* @return なし
*/
void CameraInfo::Draw()
{
#ifdef _DEBUG
	if (ImGui::TreeNode("Camera")) {
		//ImGui::SliderFloat("Pos x", &m_vNowEye.x, -1000.0f, 500.0f);
		//ImGui::SliderFloat("Pos y", &m_vNowEye.y, -1000.0f, 500.0f);
		//ImGui::SliderFloat("Pos z", &m_vNowEye.z, -1000.0f, 500.0f);
		//ImGui::SliderFloat("Look x", &m_vNowLook.x, -500.0f, 500.0f);
		//ImGui::SliderFloat("Look y", &m_vNowLook.y, -500.0f, 500.0f);
		//ImGui::SliderFloat("Look z", &m_vNowLook.z, -500.0f, 500.0f);		
		Vector3 te2 = m_Parent->GetTransform().position;
		ImGui::SliderFloat("Pos x", &te2.x, -1000.0f, 500.0f);
		ImGui::SliderFloat("Pos y", &te2.y, -1000.0f, 500.0f);
		ImGui::SliderFloat("Pos z", &te2.z, -1000.0f, 500.0f);
		ImGui::TreePop();
	}
#endif
}

void CameraInfo::UpdateMatrix()
{
	XMFLOAT3 pos;
	XMFLOAT3 look;
	XMFLOAT3 up;

	Vector3 cameraPos = m_Parent->GetTransform().position;
	Vector3 cameraUP = m_Parent->GetTransform().GetUp();

	pos = XMFLOAT3(cameraPos.x, cameraPos.y, cameraPos.z);
	look = XMFLOAT3(m_vLook.x, m_vLook.y, m_vLook.z);
	up = XMFLOAT3(m_vUp.x, m_vUp.y, m_vUp.z);

	// ビュー変換更新
	XMStoreFloat4x4(&m_View,
		XMMatrixLookAtLH(XMLoadFloat3(&pos), XMLoadFloat3(&look), XMLoadFloat3(&up)));

	// 射影変換更新
	XMStoreFloat4x4(&m_Proj, XMMatrixPerspectiveFovLH(m_fFOVY, m_fAspect, m_fNearZ, m_fFarZ));
}
XMFLOAT4X4& CameraInfo::GetView() { return m_View; }
XMFLOAT4X4& CameraInfo::GetProj() { return m_Proj; }
XMFLOAT3 CameraInfo::GetEye() { return XMFLOAT3(m_Parent->GetTransform().position.x, m_Parent->GetTransform().position.y, m_Parent->GetTransform().position.z); }

// EOF