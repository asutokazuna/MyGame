/**
 * @file TowerCollision
 * @brief TowerCollision�N���X
 */
#include "TowerCollision.h"
#include "GameObject.h"
#include "TowerEnergy.h"
#include "MissileMove.h"

HRESULT TowerCollision::Init()
{/*
	m_tag = COL_TOWER;
	size = { 45,45,45 };
	pos = m_Parent->GetTransform().position;*/
	Collision::Init();

	return E_NOTIMPL;
}
/**
 * @brief �����蔻��
 * @param[in] ���������I�u�W�F�N�g
 * @return �Ȃ�
 */
void TowerCollision::OnCollisionEnter(GameObject* othor)
{
	if (othor->CompareTag(OBJ_TAG_PLAYERMISSILE)) {
		m_Parent->GetComponent<TowerEnergy>()->AddEnergy(1);
		othor->GetComponent<MissileMove>()->m_nLife = 0;
	}
	if (othor->CompareTag(OBJ_TAG_ENEMYMISSILE)) {
		m_Parent->GetComponent<TowerEnergy>()->AddEnergy(-1);
		othor->GetComponent<MissileMove>()->m_nLife = 0;
	}
}

// EOF