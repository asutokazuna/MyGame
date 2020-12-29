/**
 * @file�@WeaponBulletCount
 * @brief ����̎c��c�e���̕\���R���|�[�l���g
 */
#include "WeaponBulletCount.h"
#include "GameObject.h"
#include "WeaponCtrl.h"
#include "Weapon.h"
#include "NumberList.h"
#include "NumberListCtrl.h"

static WeaponCtrl* WeapCtrl;

/**
 * @brief ����������
 * @return �Ȃ�
 */
HRESULT WeaponBulletCount::Init()
{
	m_BulletNum = m_Parent->GetChild<NumberList>("BulletUI");
	WeapCtrl = m_Parent->GetChild<Weapon>()->GetComponent<WeaponCtrl>();
	const int& num = WeapCtrl->GetBulletCnt();
	m_BulletNum->GetComponent<NumberListCtrl>()->SetNumber(num);
	m_BulletNum->GetComponent<NumberListCtrl>()->SetPos(Vector3(100,0,0));
	//m_BulletNum->GetComponent<NumberListCtrl>()->SetWidth(20);

	return E_NOTIMPL;
}

void WeaponBulletCount::Update()
{
	const int& num = WeapCtrl->GetBulletCnt();
	m_BulletNum->GetComponent<NumberListCtrl>()->SetNumber(num);

}

// EOF