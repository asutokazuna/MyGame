/**
 * @file PlayerShotDir.h
 * @brief プレイヤーの玉の発射方向を判定する
 */
#include "PlayerShotDir.h"
#include "GameObject.h"
#include "collision.h"
#include "Transform.h"
#include "CCamera.h"
#include "ImGui\imgui.h"
#include "ObjectManager.h"
#include <vector>
#include <list>

Vector3 size = Vector3(50, 50, 1200);

bool AABB(Transform myObj, Transform otherObj)
{
	Vector3 mySize = myObj.scale / 2;
	Vector3 otherSize = otherObj.scale / 2;

	if (myObj.position.x + mySize.x > otherObj.position.x - otherSize.x &&
		myObj.position.x - mySize.x < otherObj.position.x + otherSize.x) {
		return true;
	}
	return false;
}

/**
 * @brief 初期化処理
 * @return なし
 */
void PlayerShotDir::Awake()
{
	m_target = nullptr;
}

HRESULT PlayerShotDir::Init()
{
	m_PlayerTrans = &CCamera::Get()->GetTransform();
	//m_PlayerTrans = &m_Parent->GetParent()->GetTransform();
	m_ParentTrans = &m_Parent->GetTransform();

	m_ParentTrans->position = m_PlayerTrans->position;
	m_ParentTrans->position.z = m_PlayerTrans->position.z + size.z / 2 + 520;
	m_ParentTrans->scale = size;
	return E_NOTIMPL;
}

Vector3 pos = { 0,0,1 };
/**
 * @brief 更新処理
 * @return　なし
 */
void PlayerShotDir::LateUpdate()
{
	Vector3 test = Vector3(0,0,size.z / 2);

	pos = { 0,0,1 };
	m_ParentTrans->position = m_PlayerTrans->position;
	//m_ParentTrans->position.z = m_ParentTrans->position.z + size.z / 2;
	m_ParentTrans->position += MyMath::PosxQuaternion(test, m_PlayerTrans->quaternion);
	m_ParentTrans->quaternion = m_PlayerTrans->quaternion;
	pos = MyMath::PosxQuaternion(pos, m_PlayerTrans->quaternion);

	if (m_target != nullptr) {
		//if (AABB(*m_ParentTrans, m_target->GetTransform()) == false) {
		if (Collision::CheckOBB(*m_ParentTrans, m_target->GetTransform()) == false) {
			m_target = nullptr;
		}
	}

	std::list< GameObject*> objlist = ObjectManager::GetInstance().FindObjectsWithTag(OBJ_TAG_TOWER);
	GameObject* obj = ObjectManager::GetInstance().FindWithTag(OBJ_TAG_TOWER);
}

void PlayerShotDir::Draw()
{
#ifdef _DEBUG
	ImGui::Begin("DirPos");
	ImGui::SliderFloat("m_move x", &m_ParentTrans->position.x, -1000.0f, 500.0f);
	ImGui::SliderFloat("m_move y", &m_ParentTrans->position.y, -1000.0f, 500.0f);
	ImGui::SliderFloat("m_move z", &m_ParentTrans->position.z, -1000.0f, 500.0f);
	ImGui::End();
#endif
}

/**
 * @brief 当たっている敵の取得
 * @return 当たっている敵
 */
GameObject * PlayerShotDir::GetTarget()
{
	return m_target;
}

/**
 * @brief 当たり判定処理
 * @return なし
 */
void PlayerShotDir::OnCollisionEnter(GameObject* other)
{
	if (other->GetTag() == OBJ_TAG_TOWER) 
	{
		if(m_target != other)
		m_target = other;
	}
}

// EOF