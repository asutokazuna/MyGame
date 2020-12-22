#include "WeaponBulletCount.h"
#include "DigitNumber.h"
#include "GameObject.h"
#include "NumberDrawer.h"
#include "WeaponCtrl.h"
#include "Weapon.h"

static WeaponCtrl* WeapCtrl;

HRESULT WeaponBulletCount::Init()
{
	m_BulletNum = m_Parent->GetChildren<DigitNumber>();
	WeapCtrl = m_Parent->GetChild<Weapon>()->GetComponent<WeaponCtrl>();
	int i = 0;
	for (auto o : m_BulletNum)
	{
		o->GetTransform().position = Vector3(200 - 50 * i, 0, 0);
		i++;
	}
	return E_NOTIMPL;
}

void WeaponBulletCount::Update()
{
	const int& num = WeapCtrl->GetBulletCnt();
	int work = num;
	int value = 0;

	for (auto obj : m_BulletNum)
	{
		value = work % 10;
		obj->GetComponent<NumberDrawer>()->SetNumber(value);
		work /= 10;
	}
}

// EOF