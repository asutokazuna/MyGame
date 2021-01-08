﻿/**
 * @file CTPCamera.cpp
 * @brief 三人称カメラ
 */
#include "CTPCamera.h"
#include "CPlayer.h"
#include "MyMath.h"
#include "Transform.h"

// 定数
namespace {	// 空のnamespaceを付けるとこのcppだけのグローバル変数になる
	const Vector3 g_vEye (0.0f, 50.0f, -150.0f);
	const Vector3 g_vLook(0.0f, 50.0f, 0.0f);
	const Vector3 g_vUp(0.0f, 1.0f, 0.0f);
}

/**
 * @brief 初期化処理
 * @return なし
 */
void CTPCamera::Awake()
{
	HRESULT hr = S_OK;
	m_isActive = false;
	m_vLook = g_vLook;
	m_fFOVY = XMConvertToRadians(45);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fNearZ = 10.0f;
	m_fFarZ = 10000.0f;
	m_vUp = g_vUp;
	transform->position = g_vEye;
	UpdateMatrix();
}

HRESULT CTPCamera::Init()
{
	if (m_transform != NULL) {
		transform->position +=  m_transform->position;
		m_vLook =  m_transform->position + g_vLook;
	}
	UpdateMatrix();
	return E_NOTIMPL;
}

void CTPCamera::Uninit()
{
	CCamera::Uninit();
}
static XMFLOAT4X4 mmtxWorld;
static Transform mtrs;
/**
 * @brief 更新処理
 * @return なし
 */
void CTPCamera::LateUpdate()
{
	Transform* trs = this->transform;
	if (m_transform != nullptr) {
		//trs = m_transform;
		mtrs = *m_transform;

	}
	mtrs.localPosition = Vector3(g_vEye.x, g_vEye.y, g_vEye.z);
	//m_vLook = m_transform->position + g_vLook;

	transform->quaternion = mtrs.quaternion;

	mmtxWorld =
		MyMath::StoreXMFloat4x4(mtrs);
	mtrs.localPosition = Vector3(g_vLook.x, g_vLook.y, g_vLook.z);
	XMFLOAT4X4 mtxWorld = MyMath::StoreXMFloat4x4(mtrs);

	Vector3 pos = Vector3(mmtxWorld._41, mmtxWorld._42, mmtxWorld._43);
	Vector3 look = Vector3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
	mtrs.localPosition = Vector3(g_vUp.x, g_vUp.y, g_vUp.z);
	mtxWorld = MyMath::StoreXMFloat4x4(mtrs);
	m_vUp = MyMath::PosxQuaternion(g_vUp, transform->quaternion);
	//m_vUp = Vector3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

//	transform->position = pos;
//	m_vLook = look;

	// 始点と注視点を移動、上方ベクトルを回転
	XMMATRIX world = XMLoadFloat4x4(&mtxWorld);
	//XMStoreFloat3(&m_vEye , XMVector3TransformCoord (XMLoadFloat3(&g_vEye), world));
	//XMStoreFloat3(&m_vLook, XMVector3TransformCoord (XMLoadFloat3(&g_vLook), world));
	//XMStoreFloat3(&m_vUp  , XMVector3TransformNormal(XMLoadFloat3(&g_vUp), world));

	const float ratio = 0.9f;
	transform->position = transform->position * ratio + pos * (1 - ratio);
	m_vLook = m_vLook * ratio + look * (1 - ratio);
	// 始点、注視点、上方ベクトルを近づける
	//m_vNowEye.x = m_vNowEye.x   * ratio + m_vEye.x  * (1 - ratio);
	//m_vNowEye.y = m_vNowEye.y   * ratio + m_vEye.y  * (1 - ratio);
	//m_vNowEye.z = m_vNowEye.z   * ratio + m_vEye.z  * (1 - ratio);
	//m_vNowLook.x = m_vNowLook.x * ratio + m_vLook.x * (1 - ratio);
	//m_vNowLook.y = m_vNowLook.y * ratio + m_vLook.y * (1 - ratio);
	//m_vNowLook.z = m_vNowLook.z * ratio + m_vLook.z * (1 - ratio);
	//m_vNowUp.x = m_vNowUp.x     * ratio + m_vUp.x   * (1 - ratio);
	//m_vNowUp.y = m_vNowUp.y     * ratio + m_vUp.y   * (1 - ratio);
	//m_vNowUp.z = m_vNowUp.z     * ratio + m_vUp.z   * (1 - ratio);

	// 行列更新
	CCamera::UpdateMatrix();
}

void CTPCamera::Draw()
{
#ifdef _DEBUG
	if (ImGui::TreeNode("TPCamera")) {
		Vector3 pos = transform->position;
		ImGui::SliderFloat("pos x", &pos.x, -1000.0f, 500.0f);
		ImGui::SliderFloat("pos y", &pos.y, -1000.0f, 500.0f);
		ImGui::SliderFloat("pos z", &pos.z, -1000.0f, 500.0f);
		ImGui::SliderFloat("Look x", &m_vLook.x, -1000.0f, 500.0f);
		ImGui::SliderFloat("Look y", &m_vLook.y, -1000.0f, 500.0f);
		ImGui::SliderFloat("Look z", &m_vLook.z, -1000.0f, 500.0f);
		ImGui::SliderFloat("UP x", &m_vUp.x, -1.0f, 1.0f);
		ImGui::SliderFloat("UP y", &m_vUp.y, -1.0f, 1.0f);
		ImGui::SliderFloat("UP z", &m_vUp.z, -1.0f, 1.0f);
		//Vector3 te2 = mtrs.GetForward();
		//ImGui::SliderFloat("transfor x", &te2.x, -1.0f, 1.0f);
		//ImGui::SliderFloat("transfor y", &te2.y, -1.0f, 1.0f);
		//ImGui::SliderFloat("transfor z", &te2.z, -1.0f, 1.0f);

		Vector3 te = transform->GetUp();
		ImGui::SliderFloat("GetUp x", &te.x, -1.0f, 1.0f);
		ImGui::SliderFloat("GetUp y", &te.y, -1.0f, 1.0f);
		ImGui::SliderFloat("GetUp z", &te.z, -1.0f, 1.0f);
		//Vector3 tete = mtrs.GetUp();
		//ImGui::SliderFloat("GetUp x", &tete.x, -1.0f, 1.0f);
		//ImGui::SliderFloat("GetUp y", &tete.y, -1.0f, 1.0f);
		//ImGui::SliderFloat("GetUp z", &tete.z, -1.0f, 1.0f);
		//Vector3 qut = transform->quaternion.x;
		ImGui::SliderFloat("qut x", &transform->quaternion.x, -1.0f, 1.0f);
		ImGui::SliderFloat("qut y", &transform->quaternion.y, -1.0f, 1.0f);
		ImGui::SliderFloat("qut z", &transform->quaternion.z, -1.0f, 1.0f);
		ImGui::TreePop();
	}
#endif
}

// EOF