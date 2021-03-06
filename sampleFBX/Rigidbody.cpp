﻿/**
 * @file Rigidbody
 * @brief 物理挙動
 * @author Ariga
 */
#include "Rigidbody.h"
#include "GameObject.h"
#include "Transform.h"
#include "collision.h"

#define RESIST (1)

float Rigidbody::gravity = 0.98f;

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT Rigidbody::Init()
{
	parentTrans = &m_Parent->GetTransform();
	oldPosY = parentTrans->position.y;
	m_col = m_Parent->GetComponent<Collision>();

	force = Vector3();
	subforce = Vector3();

	return E_NOTIMPL;
}

/**
 * @brief 更新処理
 * @return なし
 */
void Rigidbody::Update()
{
	//if (oldPosY == parentTrans->position.y) {
	//	force.y = 0;
	//}
	oldPosY = parentTrans->position.y;
	parentTrans->position += force;

	force.y -= gravity;
	if (force.x < RESIST && force.x > -RESIST) {
		force.x = 0;
		subforce.x = 0;
	}
	if (force.z < RESIST && force.z > -RESIST) {
		force.z = 0;
		subforce.z = 0;
	}

	force += subforce;
}

/**
 * @brief 物体に力を加える
 * @param[in]	force	加える力
 * @return なし
 */
void Rigidbody::AddForce(Vector3 force)
{
	this->force = force;
	if (this->force.x != 0) {
		subforce.x = this->force.x / this->force.x;
	}
	if (this->force.y != 0) {
		subforce.y = gravity;
	}
	if (this->force.z != 0) {
		subforce.z = this->force.z / this->force.z;
	}
	subforce *= -RESIST;
}

// EOF