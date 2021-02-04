/**
 * @file　WeaponBulletCount
 * @brief 武器の残り残弾数の表示コンポーネント
 */
#include "WeaponBulletCount.h"
#include "GameObject.h"
#include "WeaponCtrl.h"
#include "Weapon.h"
#include "NumberList.h"
#include "NumberListCtrl.h"

static WeaponCtrl* WeapCtrl;

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT WeaponBulletCount::Init()
{
	m_BulletNum = m_Parent->GetChildTest("BulletUI");
	WeapCtrl = m_Parent->GetChildTest("Weapon")->GetComponent<WeaponCtrl>();
	const int& num = WeapCtrl->GetBulletCnt();
	m_BulletNum->GetComponent<NumberListCtrl>()->SetNumber(num);
	m_BulletNum->GetComponent<NumberListCtrl>()->SetPos(Vector3(100,0,0));
	m_BulletNum->GetComponent<NumberListCtrl>()->SetWidth(20);

	return E_NOTIMPL;
}

void WeaponBulletCount::Update()
{
	const int& num = WeapCtrl->GetBulletCnt();
	m_BulletNum->GetComponent<NumberListCtrl>()->SetNumber(num);

}

// EOF