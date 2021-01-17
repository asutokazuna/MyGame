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
Vector3 pos;
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


	mmtxWorld =
		MyMath::StoreXMFloat4x4(mtrs);
	mtrs.localPosition = Vector3(g_vLook.x, g_vLook.y, g_vLook.z);
	XMFLOAT4X4 mtxWorld = MyMath::StoreXMFloat4x4(mtrs);

	pos = Vector3(mmtxWorld._41, mmtxWorld._42, mmtxWorld._43);
	Vector3 look = Vector3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
	mtrs.localPosition = Vector3(g_vUp.x, g_vUp.y, g_vUp.z);
	mtxWorld = MyMath::StoreXMFloat4x4(mtrs);
	//m_vUp = Vector3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

//	transform->position = pos;
//	m_vLook = look;

	// 始点と注視点を移動、上方ベクトルを回転
	XMMATRIX world = XMLoadFloat4x4(&mtxWorld);
	//XMStoreFloat3(&m_vEye , XMVector3TransformCoord (XMLoadFloat3(&g_vEye), world));
	//XMStoreFloat3(&m_vLook, XMVector3TransformCoord (XMLoadFloat3(&g_vLook), world));
	//XMStoreFloat3(&m_vUp  , XMVector3TransformNormal(XMLoadFloat3(&g_vUp), world));

	const float ratioX = 0.93f;
	const float ratioY = 0.5f;
	const float ratioZ = 0.7f;
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

	add += (transform->GetRight())	* MyMath::Dot(transform->GetRight(), transform->position)	*ratioX + (transform->GetRight())	* MyMath::Dot(transform->GetRight(), pos)	* (1 - ratioX);
	add += (transform->GetUp())		* MyMath::Dot(transform->GetUp(), transform->position)		*ratioY + (transform->GetUp())		* MyMath::Dot(transform->GetUp(), pos)		* (1 - ratioY);
	add += (transform->GetForward())* MyMath::Dot(transform->GetForward(), transform->position) *ratioZ + (transform->GetForward())	* MyMath::Dot(transform->GetForward(), pos) * (1 - ratioZ);
	transform->position = add;

	Vector3 lookadd = Vector3();
	lookadd += (transform->GetRight())	* MyMath::Dot(transform->GetRight(), m_vLook)	*ratioX + (transform->GetRight())	* MyMath::Dot(transform->GetRight(), look)	* (1 - ratioX);
	lookadd += (transform->GetUp())		* MyMath::Dot(transform->GetUp(), m_vLook)		*ratioY + (transform->GetUp())		* MyMath::Dot(transform->GetUp(), look)		* (1 - ratioY);
	lookadd += (transform->GetForward())* MyMath::Dot(transform->GetForward(), m_vLook) *ratioZ + (transform->GetForward())	* MyMath::Dot(transform->GetForward(), look) * (1 - ratioZ);
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
}

void CTPCamera::Draw()
{
#ifdef _DEBUG
	if (ImGui::TreeNode("TPCamera")) {
		ImGui::SliderFloat("pos x", &pos.x, -1000.0f, 500.0f);
		ImGui::SliderFloat("pos y", &pos.y, -1000.0f, 500.0f);
		ImGui::SliderFloat("pos z", &pos.z, -1000.0f, 500.0f);
		ImGui::SliderFloat("eyepos x", &transform->position.x, -1000.0f, 500.0f);
		ImGui::SliderFloat("eyepos y", &transform->position.y, -1000.0f, 500.0f);
		ImGui::SliderFloat("eyepos z", &transform->position.z, -1000.0f, 500.0f);
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