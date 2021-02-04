#include "EnemyWeaponCtrl.h"
#include "GameObject.h"
#include "collision.h"
#include "WeaponCtrl.h"

#define MAX_BULLET (20)

HRESULT EnemyWeaponCtrl::Init()
{
	std::list<GameObject*> *missileList = m_Parent->GetComponent<WeaponCtrl>()->GetMissileList();
	m_Parent->GetComponent<WeaponCtrl>()->SetMaxBullet(MAX_BULLET);

	for (auto missile : *missileList)
	{
		missile->SetTag(OBJ_TAG_ENEMYMISSILE);
	}

	return E_NOTIMPL;
}
