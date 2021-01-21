/**
 * @file CTPCamera.cpp
 * @brief 三人称カメラ
 */
#include "CTPCamera.h"
#include "CPlayer.h"
#include "MyMath.h"
#include "Transform.h"
#include "input.h"
#include "ObjectManager.h"
#include "CPlayer.h"

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
	m_pos = m_oldPos = Vector3();
	UpdateMatrix();
}

HRESULT CTPCamera::Init()
{
	if (m_transform == NULL) {
		m_transform = &ObjectManager::GetInstance().FindObject<GameObject>("Player")->GetTransform();
	}
	transform->position +=  m_transform->position;
	m_vLook =  m_transform->position + g_vLook;

	Vector3 dir = transform->position - m_vLook;
	transform->quaternion = MyMath::LookAt(dir);
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
	if (m_isActive == false) {
		return;
	}
	Transform* trs = this->transform;
	if (m_transform != nullptr) {
		//trs = m_transform;
		mtrs = *m_transform;

	}
	m_oldPos = m_pos;
	mtrs.localPosition = Vector3(g_vEye.x, g_vEye.y, g_vEye.z);
	//m_vLook = m_transform->position + g_vLook;


	mmtxWorld =
		MyMath::StoreXMFloat4x4(mtrs);
	mtrs.localPosition = Vector3(g_vLook.x, g_vLook.y, g_vLook.z);
	XMFLOAT4X4 mtxWorld = MyMath::StoreXMFloat4x4(mtrs);

	m_pos = Vector3(mmtxWorld._41, mmtxWorld._42, mmtxWorld._43);
	Vector3 look = Vector3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
	mtrs.localPosition = Vector3(g_vUp.x, g_vUp.y, g_vUp.z);
	mtxWorld = MyMath::StoreXMFloat4x4(mtrs);
	//m_vUp = Vector3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

//	transform->position = pos;
//	m_vLook = look;


	if (m_pos.x != m_oldPos.x ||
		m_pos.y != m_oldPos.y || 
		m_pos.z != m_oldPos.z) {
		m_threshold = 0.01f;
	}

	// 始点と注視点を移動、上方ベクトルを回転
	XMMATRIX world = XMLoadFloat4x4(&mtxWorld);
	//XMStoreFloat3(&m_vEye , XMVector3TransformCoord (XMLoadFloat3(&g_vEye), world));
	//XMStoreFloat3(&m_vLook, XMVector3TransformCoord (XMLoadFloat3(&g_vLook), world));
	//XMStoreFloat3(&m_vUp  , XMVector3TransformNormal(XMLoadFloat3(&g_vUp), world));

	const float ratioX = 0.5f;
	const float ratioY = 0.2f;
	const float ratioZ = 0.0f;
	Vector3 add = Vector3();
	/*
	// x,y,z軸
	add.x = transform->position.x * ratioX + pos.x * (1 - ratioX);
	add.y = transform->position.y * ratioY + pos.y * (1 - ratioY);
	add.z = transform->position.z * ratioZ + pos.z * (1 - ratioZ);
	transform->position = add;
	*/

	//add += transform->position * MyMath::Abs(transform->GetRight())	*ratioX + MyMath::Abs(transform->GetRight())	* pos * (1 - ratioX);
	//add += transform->position * MyMath::Abs(transform->GetUp())		*ratioY + MyMath::Abs(transform->GetUp())		* pos * (1 - ratioY);
	//add += transform->position * MyMath::Abs(transform->GetForward())	*ratioZ + MyMath::Abs(transform->GetForward())	* pos * (1 - ratioZ);
	//transform->position = add;

	Vector3 rightPos, righteyepos;
	Vector3 rightLook, righteyeLook;
	Vector3 upPos, upeyepos;
	Vector3 upLook, upeyeLook;
	Vector3 forwardPos, forwardeyepos;
	Vector3 forwardLook, forwardeyeLook;

	righteyepos = (transform->GetRight()) * MyMath::Dot(transform->GetRight(), transform->position);
	rightPos = (transform->GetRight()) * MyMath::Dot(transform->GetRight(), m_pos);
	upeyepos = (transform->GetUp()) * MyMath::Dot(transform->GetUp(), transform->position);
	upPos = (transform->GetUp()) * MyMath::Dot(transform->GetUp(), m_pos);
	forwardeyepos = (transform->GetForward()) * MyMath::Dot(transform->GetForward(), transform->position);
	forwardPos = (transform->GetForward()) * MyMath::Dot(transform->GetForward(), m_pos);

	float ttt = m_threshold;
	add += MyMath::InQuint(ratioX +(1 - ratioX) * ttt, rightPos, righteyepos);
	add += MyMath::Lerp(upeyepos, upPos, ratioY + (1 - ratioY) * ttt);
	add += MyMath::OutQuint(ratioZ + (1 - ratioZ) * ttt,forwardPos, forwardeyepos);
	//if (add.x > 1000 ||
	//	add.z > 1000) {
	//	add = add;
	//}

	//Vector3 none;
	//none = MyMath::Slerp(righteyepos, rightPos, ttt);

	//add += (transform->GetRight())	* MyMath::Dot(transform->GetRight(), transform->position)	*ratioX + (transform->GetRight())	* MyMath::Dot(transform->GetRight(), m_pos)	* (1 - ratioX);
	//add += (transform->GetUp())		* MyMath::Dot(transform->GetUp(), transform->position)		*ratioY + (transform->GetUp())		* MyMath::Dot(transform->GetUp(), m_pos)		* (1 - ratioY);
	//add += (transform->GetForward())* MyMath::Dot(transform->GetForward(), transform->position) *ratioZ + (transform->GetForward())	* MyMath::Dot(transform->GetForward(), m_pos) * (1 - ratioZ);
	transform->position = add;

	righteyeLook = (transform->GetRight()) * MyMath::Dot(transform->GetRight(), m_vLook);
	rightLook = (transform->GetRight()) * MyMath::Dot(transform->GetRight(), look);
	upeyeLook = (transform->GetUp()) * MyMath::Dot(transform->GetUp(), m_vLook);
	upLook = (transform->GetUp()) * MyMath::Dot(transform->GetUp(), look);
	forwardeyeLook = (transform->GetForward()) * MyMath::Dot(transform->GetForward(), m_vLook);
	forwardLook = (transform->GetForward()) * MyMath::Dot(transform->GetForward(), look);

	Vector3 lookadd = Vector3();
	lookadd += MyMath::InQuint(ratioX + (1 - ratioX) * ttt, rightLook, righteyeLook);

	lookadd += MyMath::Lerp(upeyeLook, upLook, ratioY + ratioY * ttt);
	lookadd += MyMath::OutQuint(ratioZ + (1 - ratioZ) * ttt, forwardLook, forwardeyeLook);

	//lookadd += (transform->GetRight())	* MyMath::Dot(transform->GetRight(), m_vLook)	*ratioX + (transform->GetRight())	* MyMath::Dot(transform->GetRight(), look)	* (1 - ratioX);
	//lookadd += (transform->GetUp())		* MyMath::Dot(transform->GetUp(), m_vLook)		*ratioY + (transform->GetUp())		* MyMath::Dot(transform->GetUp(), look)		* (1 - ratioY);
	//lookadd += (transform->GetForward())* MyMath::Dot(transform->GetForward(), m_vLook) *ratioZ + (transform->GetForward())	* MyMath::Dot(transform->GetForward(), look) * (1 - ratioZ);
	m_vLook = lookadd;


	//add = pos - transform->position;
	//Vector3 move = Vector3();
	//move += transform->GetRight() * pos.x;
	//transform->position += add;


	//transform->position = transform->position * ratioX + pos * (1 - ratioX);
	//m_vLook = m_vLook * ratioX + look * (1 - ratioX);
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

	Vector3 dir = m_vLook - transform->position;
	transform->quaternion = MyMath::LookAt(dir);
	m_vUp = MyMath::PosxQuaternion(g_vUp, transform->quaternion);
	// 行列更新
	CCamera::UpdateMatrix();

	if (m_threshold < 1) {
		m_threshold += 0.001f;
	}
}

void CTPCamera::Draw()
{
#ifdef _DEBUG
	if (ImGui::TreeNode("TPCamera")) {
		ImGui::RadioButton("changePos", m_pos != m_oldPos);
		ImGui::SliderFloat("pos x", &m_pos.x, -1000.0f, 500.0f);
		ImGui::SliderFloat("pos y", &m_pos.y, -1000.0f, 500.0f);
		ImGui::SliderFloat("pos z", &m_pos.z, -1000.0f, 500.0f);
		ImGui::SliderFloat("eyepos x", &transform->position.x, -1000.0f, 500.0f);
		ImGui::SliderFloat("eyepos y", &transform->position.y, -1000.0f, 500.0f);
		ImGui::SliderFloat("eyepos z", &transform->position.z, -1000.0f, 500.0f);
		ImGui::SliderFloat("Look x", &m_vLook.x, -1000.0f, 500.0f);
		ImGui::SliderFloat("Look y", &m_vLook.y, -1000.0f, 500.0f);
		ImGui::SliderFloat("Look z", &m_vLook.z, -1000.0f, 500.0f);
		ImGui::SliderFloat("UP x", &m_vUp.x, -1.0f, 1.0f);
		ImGui::SliderFloat("UP y", &m_vUp.y, -1.0f, 1.0f);
		ImGui::SliderFloat("UP z", &m_vUp.z, -1.0f, 1.0f);
		ImGui::SliderFloat("m_threshold", &m_threshold, -1.0f, 1.0f);
		//Vector3 te2 = mtrs.GetForward();
		//ImGui::SliderFloat("transfor x", &te2.x, -1.0f, 1.0f);
		//ImGui::SliderFloat("transfor y", &te2.y, -1.0f, 1.0f);
		//ImGui::SliderFloat("transfor z", &te2.z, -1.0f, 1.0f);

		Vector3 te = transform->GetUp();
		ImGui::SliderFloat("GetUp x", &te.x, -1.0f, 1.0f);
		ImGui::SliderFloat("GetUp y", &te.y, -1.0f, 1.0f);
		ImGui::SliderFloat("GetUp z", &te.z, -1.0f, 1.0f);
		Vector3 tete = transform->GetForward();
		ImGui::SliderFloat("GetForward x", &tete.x, -1.0f, 1.0f);
		ImGui::SliderFloat("GetForward y", &tete.y, -1.0f, 1.0f);
		ImGui::SliderFloat("GetForward z", &tete.z, -1.0f, 1.0f);
		//Vector3 qut = transform->quaternion.x;
		ImGui::SliderFloat("qut x", &transform->quaternion.x, -1.0f, 1.0f);
		ImGui::SliderFloat("qut y", &transform->quaternion.y, -1.0f, 1.0f);
		ImGui::SliderFloat("qut z", &transform->quaternion.z, -1.0f, 1.0f);
		ImGui::TreePop();
	}
#endif
}

// EOF