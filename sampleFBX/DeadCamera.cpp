/**
 * @file DeadCamera 
 * @brief プレイヤー死亡時のカメラオブジェクト
 */
#include "DeadCamera.h"
#include "ObjectManager.h"
#include "MyMath.h"

 // 定数
namespace {	// 空のnamespaceを付けるとこのcppだけのグローバル変数になる
	const Vector3 g_vEye(0.0f, 50.0f, -150.0f);
	const Vector3 g_vLook(0.0f, 50.0f, 0.0f);
	const Vector3 g_vUp(0.0f, 1.0f, 0.0f);
}

HRESULT DeadCamera::Init()
{
	transform->position = CCamera::Get()->GetTransform().position;
	transform->quaternion = CCamera::Get()->GetTransform().quaternion;
	m_vLook = CCamera::Get()->GetLook();	

	m_player = ObjectManager::GetInstance().FindObject<GameObject>("Player");
	m_startPos = transform->position;

	m_endPos = transform->position + transform->GetForward() * -200;

	Vector3 dir = m_player->GetTransform().position - m_startPos;
	Quaternion quat = MyMath::LookAt(dir);
	m_endPos = transform->position + MyMath::PosxQuaternion(Vector3(0, 0, 1), quat) * -200;

	m_threshold = 0;
	return E_NOTIMPL;
}

void DeadCamera::LateUpdate()
{
	if (m_isActive == false) {
		return;
	}

	transform->position = MyMath::Lerp(m_startPos, m_endPos, m_threshold);
	m_vLook = MyMath::Lerp(m_vLook, m_player->GetTransform().position, m_threshold);


	m_threshold += 0.01f;
	Vector3 dir = m_vLook - transform->position;
	transform->quaternion = MyMath::LookAt(dir);
	m_vUp = MyMath::PosxQuaternion(g_vUp, transform->quaternion);

	UpdateMatrix();
}

// EOF