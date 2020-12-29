/**
 * @file CoreCollision
 * @brief CoreCollisionクラス
 */
#include "CoreCollision.h"
#include "GameObject.h"
#include "CoreState.h"
#include "MissileMove.h"
#include "TowerManager.h"
#include "TowerMgrCtrl.h"
#include "ObjectManager.h"
#include "MissileCtrl.h"

CoreCollision::CoreCollision():m_isInvincible(true), m_OpponentBulletTag(0),m_OpponentTower(0)
{
}

void CoreCollision::Update()
{
	// 塔の占拠数で無敵切り替え
	m_isInvincible = ObjectManager::GetInstance().FindObject<GameObject>("TowerManager")->GetComponent<TowerMgrCtrl>()->IsOccupation(m_OpponentTower);
}

void CoreCollision::OnCollisionEnter(GameObject* gameObj)
{

	if (gameObj->CompareTag(m_OpponentBulletTag))
	{
		if (m_isInvincible == false) 
		{
			int power = gameObj->GetComponent<MissileCtrl>()->GetPower();
			m_Parent->GetComponent<CoreState>()->AddLife(-power);
		}
		gameObj->SetActive(false);
	}
	//if (othor->GetTag() == m_ColTarget ) {
	//	if(TowerManager::m_isAttack == this->m_tag)
	//	m_Parent->GetComponent<CoreState>()->AddLife(-1);
	//	othor->m_Parent->GetComponent<MissileMove>()->m_nLife = 0;
	//}
}

/**
 * @brief オブジェクトタグ
 */
void CoreCollision::SetOpponentBullet(int kind)
{
	m_OpponentBulletTag = kind;
}

void CoreCollision::SetOpponentTower(int kind)
{
	m_OpponentTower = kind;
}

// EOF