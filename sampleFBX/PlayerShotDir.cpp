/**
 * @file PlayerShotDir.h
 * @brief プレイヤーの玉の発射方向を判定する
 */
#include "PlayerShotDir.h"
#include "GameObject.h"
#include "collision.h"
#include "Transform.h"
#include "CCamera.h"

Vector3 size = Vector3(250, 250, 1200);
Transform* g_trans;

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
	//m_ParentTrans = &CCamera::Get()->GetTransform();
	g_trans = &m_Parent->GetParent()->GetTransform();

	return E_NOTIMPL;
}

/**
 * @brief 更新処理
 * @return　なし
 */
void PlayerShotDir::Update()
{
	g_trans = &m_Parent->GetParent()->GetTransform();

	if (m_target != nullptr) {
		if (AABB(*g_trans, m_target->GetTransform()) == false) {
			m_target = nullptr;
		}
	}
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