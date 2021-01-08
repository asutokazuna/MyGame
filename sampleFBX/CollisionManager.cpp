/**
 * @file CollisionManager
 * @brief 当たり判定管理クラス
 */
#include "CollisionManager.h"
#include "GameObject.h"
#include "Object.h"

std::unordered_map<int, Collision*> CollisionManager::m_List;	//!< コライダーリスト
LinerOctreeManager<Collision> CollisionManager::m_CollisionTree;

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
	const int LEVEL = 4;
	const float length = 5000.0f;
	Vector3 MIN = Vector3(-length,-length,-length);
	Vector3 MAX = Vector3(+length,+length,+length);
	m_CollisionTree.Init(LEVEL,MIN,MAX);
}

void CollisionManager::Check()
{
	for (std::unordered_map<int, Collision*>::iterator col = m_List.begin(), colend = m_List.end(); col != colend; ++col) {
		for (std::unordered_map<int, Collision*>::iterator othor = m_List.begin(), e = colend; othor != e; ++othor) {

			if (othor == col) {
				continue;
			}
			if (col->second->GetActive() == false || othor->second->GetActive() == false ||
				col->second->m_Parent->GetActive() == false || othor->second->m_Parent->GetActive() == false) {
				continue;
			}

			Vector3 size = col->second->m_Parent->GetTransform().scale * col->second->GetoffsetSize();
			Vector3 othorsize = othor->second->m_Parent->GetTransform().scale *  othor->second->GetoffsetSize();

			/*		if (CheckBox(col->second->m_transform->position, size, othor->second->m_transform->position, othorsize)) {
						col->second->m_Parent->OnCollisionEnter((othor->second->m_Parent));
					}*//*
					Transform mytrans = *(col->second->m_transform);
					Transform othortrans = *(othor->second->m_transform);
					mytrans.scale = size;
					othortrans.scale = othorsize;*/
					//if (CheckOBB(mytrans, othortrans)) {
			if (CheckOBB(col->second->m_Parent->GetTransform(), othor->second->m_Parent->GetTransform())) {
				col->second->m_Parent->OnCollisionEnter((othor->second->m_Parent));
			}
		}
	}
}

void CollisionManager::Set(Collision* col)
{
	static int num = 0;
	col->SetID(num);
	m_List[num] = col;
	num++;
}

void CollisionManager::Delete(Collision * col)
{
	m_List.erase(col->GetID());
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

void CollisionManager::Clear()
{
	m_List.clear();
}

// EOF