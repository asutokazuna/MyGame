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
#include "Lockon.h"

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

bool IsHit(XMFLOAT4X4 world, Vector3 scale)
{
	float lenX = sqrtf(world._11 * world._11 + world._12 * world._12 + world._13 * world._13);
	float lenY = sqrtf(world._21 * world._21 + world._22 * world._22 + world._23 * world._23);
	float lenZ = sqrtf(world._31 * world._31 + world._33 * world._33 + world._33 * world._33);

	if (world._41 < 300 &&
		world._41 > -300 &&
		world._42 < 300 &&
		world._42 > -300
		) {
		return true;
	}

	return false;
}

bool IsHit(XMFLOAT4 pos, Vector3 scale)
{

	if (pos.x < SCREEN_WIDTH  / 2 +100 &&
		pos.x > SCREEN_WIDTH  / 2 -100 &&
		pos.y < SCREEN_HEIGHT / 2 +100 &&
		pos.y > SCREEN_HEIGHT / 2 -100
		) {
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
	m_target2DPos = Vector3();
}

HRESULT PlayerShotDir::Init()
{
	m_target = nullptr;
	m_target2DPos = Vector3();
	m_Lockon = m_Parent->GetChildTest("Lockon");
	m_Lockon->SetActive(false);
	//std::list<GameObject*> objlist;// = ObjectManager::GetInstance().FindObjectsWithTag(OBJ_TAG_TOWER);
	m_objlist = ObjectManager::GetInstance().FindObjectsWithTag(OBJ_TAG_CORE_ENEMY);
	m_objlist.merge(ObjectManager::GetInstance().FindObjectsWithTag(OBJ_TAG_ENEMY));
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 proj;
	XMFLOAT4X4 viewport;
	view = CCamera::Get()->GetView();
	proj = CCamera::Get()->GetProj();
	viewport._11 = SCREEN_WIDTH / 2;
	viewport._22 = -SCREEN_HEIGHT / 2;
	viewport._41 = SCREEN_WIDTH / 2;
	viewport._42 = SCREEN_HEIGHT / 2;
	XMMATRIX mtx;

	for (auto o : m_objlist)
	{
		world = MyMath::StoreXMFloat4x4(o->GetTransform());

		mtx = XMLoadFloat4x4(&world) * XMLoadFloat4x4(&view) * XMLoadFloat4x4(&proj) * XMLoadFloat4x4(&viewport);

		XMStoreFloat4x4(&world, mtx);
		if (IsHit(world, Vector3())) {
			m_target = o;
		}
	}

	return E_NOTIMPL;
}

/**
 * @brief 更新処理
 * @return　なし
 */
void PlayerShotDir::LateUpdate()
{

	XMFLOAT4 g_pos;
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 proj;
	XMFLOAT4X4 viewport = XMFLOAT4X4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
	view = CCamera::Get()->GetView();
	proj = CCamera::Get()->GetProj();
	viewport._11 = SCREEN_WIDTH / 2;
	viewport._22 = -SCREEN_HEIGHT / 2;
	viewport._41 = SCREEN_WIDTH / 2;
	viewport._42 = SCREEN_HEIGHT / 2;
	XMVECTOR vec;
	m_target = nullptr;
	for (auto o : m_objlist)
	{
		world = MyMath::StoreXMFloat4x4(o->GetTransform());
		vec = XMVector3Project(XMVectorSet(world._41, world._42, world._43,1), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, XMLoadFloat4x4(&proj), XMLoadFloat4x4(&view), XMMatrixIdentity());

		XMStoreFloat4(&g_pos, vec);
		g_pos.y = SCREEN_HEIGHT  -g_pos.y;

		// 範囲内チェック
		if (IsHit(g_pos, Vector3())) {
			m_target = o;
			m_target2DPos = Vector3(g_pos.x, g_pos.y, g_pos.z);
			m_Lockon->SetActive(true);
			m_Lockon->GetTransform().position = Vector3(m_target2DPos.x - SCREEN_WIDTH / 2, m_target2DPos.y - SCREEN_HEIGHT / 2, m_target2DPos.z);
		}
	}
	if (m_target == nullptr) {
		m_Lockon->SetActive(false);
	}

}

void PlayerShotDir::Draw()
{
#ifdef _DEBUG
	if (ImGui::TreeNode("DirPos")) {
		ImGui::SliderFloat("g_pos x", &m_target2DPos.x, -1000.0f, 500.0f);
		ImGui::SliderFloat("g_pos y", &m_target2DPos.y, -1000.0f, 500.0f);
		ImGui::SliderFloat("g_pos z", &m_target2DPos.z, -1000.0f, 500.0f);
		ImGui::TreePop();
	}
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
	//if (other->GetTag() == OBJ_TAG_TOWER) 
	//{
	//	if(m_target != other)
	//	m_target = other;
	//}
}

// EOF