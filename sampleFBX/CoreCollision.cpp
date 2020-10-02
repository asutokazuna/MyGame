/**
 * @file CoreCollision
 * @brief CoreCollisionクラス
 */
#include "CoreCollision.h"
#include "GameObject.h"
#include "CoreState.h"
#include "MissileMove.h"
#include "TowerManager.h"

CoreCollision::CoreCollision():m_ColTarget(0)
{
}

//void CoreCollision::Check(Collision * othor)
//{
//	if (othor->GetTag() == m_ColTarget ) {
//		if(TowerManager::m_isAttack == this->m_tag)
//		m_Parent->GetComponent<CoreState>()->AddLife(-1);
//		othor->m_Parent->GetComponent<MissileMove>()->m_nLife = 0;
//	}
//}


// EOF