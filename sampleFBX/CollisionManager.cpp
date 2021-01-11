/**
 * @file CollisionManager
 * @brief 当たり判定管理クラス
 */
#include "CollisionManager.h"
#include "GameObject.h"
#include "Object.h"
#include <vector>

 /**
  * @brief OBBの当たり判定
  * @param[in] myPos			自分の座標
  * @param[in] myVector		自分の座標軸
  * @param[in] myScale		自分の半分のサイズ
  * @param[in] othorPos		相手の座標
  * @param[in] othorVector	相手の座標軸
  * @param[in] othorScale	相手の半分のサイズ
  * @return 当たっていればtrue
  */
bool OBB(Vector3 myPos, Quaternion myVector, Vector3 myScale, Vector3 othorPos, Quaternion othorVector, Vector3 othorScale)
{
	Vector3 distance = othorPos - myPos;
	Vector3 right = { 1,0,0 };
	Vector3 up = { 0,1,0 };
	Vector3 forward = { 0,0,1 };

	Vector3 myRight, myUp, myForward, othorRight, othorUp, othorForward;

	myRight = MyMath::PosxQuaternion(right, myVector);
	myUp = MyMath::PosxQuaternion(up, myVector);
	myForward = MyMath::PosxQuaternion(forward, myVector);
	othorRight = MyMath::PosxQuaternion(right, othorVector);
	othorUp = MyMath::PosxQuaternion(up, othorVector);
	othorForward = MyMath::PosxQuaternion(forward, othorVector);


	Vector3 vec[6];
	vec[0] = myRight;
	vec[1] = myUp;
	vec[2] = myForward;
	vec[3] = othorRight;
	vec[4] = othorUp;
	vec[5] = othorForward;

	// 各軸方向の半分の大きさを求める
	Vector3 Length[6];
	Length[0] = vec[0] * myScale.x;
	Length[1] = vec[1] * myScale.y;
	Length[2] = vec[2] * myScale.z;
	Length[3] = vec[3] * othorScale.x;
	Length[4] = vec[4] * othorScale.y;
	Length[5] = vec[5] * othorScale.z;

	float totalLength, distVec;

	for (int i = 0; i < 6; i++)
	{
		totalLength = 0.0f;
		for (int j = 0; j < 6; j++)
		{
			totalLength += fabsf(MyMath::Dot(vec[i], Length[j]));
		}
		distVec = MyMath::Dot(vec[i], distance);

		if (totalLength < fabsf(distVec)) {
			return false;
		}
	}

	return true;
}

void CollisionManager::Init()
{
	const int LEVEL = 5;
	const float length = 5000.0f;
	Vector3 MIN = Vector3(-length,-length,-length);
	Vector3 MAX = Vector3(+length,+length,+length);
	m_CollisionTree.Init(LEVEL,MIN,MAX);
}

void CollisionManager::Uninit()
{
	for (auto &list : m_registList)
	{
		list->Remove();
	}
	m_registList.clear();
}

DWORD num = 0;

void CollisionManager::Draw()
{
#ifdef _DEBUG
	if (ImGui::TreeNode("ColNum")) {
		ImGui::Text("Num:%d", num);
		ImGui::Text("ListCnt:%d", m_registList.size());
		ImGui::TreePop();
	}
#endif
}

/**
 * @brief 当たり判定の確認
 */
void CollisionManager::Check()
{
	std::vector<Collision*> colVect;
	for (auto &list : m_registList)
	{
		Collision *col = list.get()->m_object;
		list.get()->Remove();
		if (col == NULL) {
			continue;
		}
		if (col->GetActive() == false || col->m_Parent->GetActive() == false) {
			continue;
		}
		Vector3 pos, size, min, max;
		pos = col->m_Parent->GetTransform().position;
		size = col->m_Parent->GetTransform().scale + col->GetoffsetSize();
		min = pos - size;
		max = pos + size;

		m_CollisionTree.Regist(min, max, list.get());
	}

	num = m_CollisionTree.GetAllCollisionList(colVect);

	DWORD i;
	num /= 2;
	for (i = 0; i < num; i++)
	{
		Collision* myCol = colVect[i * 2];
		Collision* othorCol = colVect[i * 2 + 1];
		GameObject* myObj = myCol->m_Parent;
		GameObject* othorObj = othorCol->m_Parent;

		if (myCol->GetActive() == false || othorCol->GetActive() == false || 
			myObj->GetActive() == false || othorObj->GetActive() == false) {
			continue;
		}

		if (CheckOBB(myObj->GetTransform(), othorObj->GetTransform(), myCol, othorCol))
		{
			myObj->OnCollisionEnter((othorObj));
			othorObj->OnCollisionEnter((myObj));
		}
	}
}

void CollisionManager::Set(Collision* col)
{
	std::unique_ptr<TreeRegisterObject<Collision>> obj = std::make_unique<TreeRegisterObject<Collision>>();
	obj->m_object = col;

	m_registList.push_back(((std::move(obj))));
}

void CollisionManager::Remove(Collision* col)
{
	for (auto it = m_registList.begin(); it != m_registList.end();)
	{
		if (it->get()->m_object = col) {
			it = m_registList.erase(it);
		}
		else {
			it++;
		}
	}
}

bool CollisionManager::CheckOBB(const Transform & myObj, const Transform & othorObj, Collision* myCol, Collision* othorCol)
{
	bool isHit = false;

	Vector3 myVec, othorVec;
	Vector3 size = myObj.scale * myCol->GetoffsetSize();
	Vector3 othorsize = othorObj.scale * othorCol->GetoffsetSize();


	myVec.x = myObj.quaternion.x;
	myVec.y = myObj.quaternion.y;
	myVec.z = myObj.quaternion.z;
	othorVec.x = othorObj.quaternion.x;
	othorVec.y = othorObj.quaternion.y;
	othorVec.z = othorObj.quaternion.z;

	isHit = OBB(myObj.position, myObj.quaternion, size, othorObj.position, othorObj.quaternion, othorsize);

	return isHit;
}
bool CollisionManager::CheckOBB(const Transform & myObj, const Transform & othorObj)
{
	bool isHit = false;

	Vector3 myVec, othorVec;
	Vector3 size = myObj.scale * GetSize(myObj);
	Vector3 othorsize = othorObj.scale * GetSize(othorObj);


	myVec.x = myObj.quaternion.x;
	myVec.y = myObj.quaternion.y;
	myVec.z = myObj.quaternion.z;
	othorVec.x = othorObj.quaternion.x;
	othorVec.y = othorObj.quaternion.y;
	othorVec.z = othorObj.quaternion.z;

	isHit = OBB(myObj.position, myObj.quaternion, size, othorObj.position, othorObj.quaternion, othorsize);

	return isHit;
}

Vector3 CollisionManager::GetSize(const Transform & trans)
{
	Vector3 size = trans.m_Parent->GetComponent<Collision>()->GetoffsetSize();
	return size;
}

// EOF