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
}

HRESULT PlayerShotDir::Init()
{
	m_PlayerTrans = &CCamera::Get()->GetTransform();
	//m_PlayerTrans = &m_Parent->GetParent()->GetTransform();
	m_ParentTrans = &m_Parent->GetTransform();

	m_ParentTrans->position = m_PlayerTrans->position;
	m_ParentTrans->position.z = m_PlayerTrans->position.z + size.z / 2 + 520;
	m_ParentTrans->scale = size;

	std::list< GameObject*> objlist = ObjectManager::GetInstance().FindObjectsWithTag(OBJ_TAG_TOWER);
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

	for (auto o : objlist)
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

Vector3 pos = { 0,0,1 };
static 
XMFLOAT4 g_pos;
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

	//if (m_target != nullptr) {
	//	//if (AABB(*m_ParentTrans, m_target->GetTransform()) == false) {
	//	if (Collision::CheckOBB(*m_ParentTrans, m_target->GetTransform()) == false) {
	//		m_target = nullptr;
	//	}
	//}
	std::list< GameObject*> objlist = ObjectManager::GetInstance().FindObjectsWithTag(OBJ_TAG_TOWER);
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
	XMMATRIX mtx;
	XMVECTOR vec;
	m_target = nullptr;
	for (auto o : objlist)
	{
		world = MyMath::StoreXMFloat4x4(o->GetTransform());

		mtx = XMMatrixMultiply( XMLoadFloat4x4(&world), XMLoadFloat4x4(&view));
		mtx*= XMLoadFloat4x4(&proj);
		mtx *= XMLoadFloat4x4(&viewport);

		vec = XMVector3Project(XMVectorSet(world._41, world._42, world._43,1), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, XMLoadFloat4x4(&proj), XMLoadFloat4x4(&view), XMMatrixIdentity());

		XMStoreFloat4x4(&world, mtx);
		XMStoreFloat4(&g_pos, vec);
		if (IsHit(g_pos, Vector3())) {
			m_target = o;
		}
	}

}

void PlayerShotDir::Draw()
{
#ifdef _DEBUG
	ImGui::Begin("DirPos");
	ImGui::SliderFloat("m_move x", &m_ParentTrans->position.x, -1000.0f, 500.0f);
	ImGui::SliderFloat("m_move y", &m_ParentTrans->position.y, -1000.0f, 500.0f);
	ImGui::SliderFloat("m_move z", &m_ParentTrans->position.z, -1000.0f, 500.0f);
	ImGui::SliderFloat("g_pos x", &g_pos.x, -1000.0f, 500.0f);
	ImGui::SliderFloat("g_pos y", &g_pos.y, -1000.0f, 500.0f);
	ImGui::SliderFloat("g_pos z", &g_pos.z, -1000.0f, 500.0f);
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
	//if (other->GetTag() == OBJ_TAG_TOWER) 
	//{
	//	if(m_target != other)
	//	m_target = other;
	//}
}

// EOF