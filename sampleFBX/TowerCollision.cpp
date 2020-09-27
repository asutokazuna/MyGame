/**
 * @file TowerCollision
 * @brief TowerCollisionƒNƒ‰ƒX
 */
#include "TowerCollision.h"
#include "GameObject.h"
#include "TowerEnergy.h"
#include "MissileMove.h"

HRESULT TowerCollision::Init()
{
	m_tag = COL_TOWER;
	size = { 45,45,45 };
	pos = m_Parent->GetTransform().position;
	Collision::Init();

	return E_NOTIMPL;
}

void TowerCollision::OnCollisionEnter(GameObject* othor)
{
	if (othor->CompareTag(COL_MISSILE)) {
		m_Parent->GetComponent<TowerEnergy>()->AddEnergy(1);
		othor->GetComponent<MissileMove>()->m_nLife = 0;
	}
	if (othor->CompareTag(COL_MISSILE_ENEMY)) {
		m_Parent->GetComponent<TowerEnergy>()->AddEnergy(-1);
		othor->GetComponent<MissileMove>()->m_nLife = 0;
	}
}

void TowerCollision::UpdatePos()
{
	pos = m_Parent->GetTransform().position;
}

// EOF