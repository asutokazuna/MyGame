/**
 * @file WeaponCtrl
 * @brief 武器の制御クラス
 */
#include "WeaponCtrl.h"
#include "Transform.h"
#include "Missile.h"
#include "GameObject.h"
#include "MissileCtrl.h"

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT WeaponCtrl::Init()
{
	m_BulletList = m_Parent->GetChildren<Missile>();
	m_ParentTrans = &m_Parent->GetTransform();
	m_BulletCount = (int)m_BulletList.size();

	m_ReloadTime = 60;
	return E_NOTIMPL;
}

void WeaponCtrl::Update()
{
	if (m_BulletCount <= 0) {
		m_ReloadTime--;
	}
	if (m_ReloadTime < 0) {
		m_BulletCount = (int)m_BulletList.size();
		m_ReloadTime = 60;
	}
}

/**
* @brief 玉の発射
* @return なし
*/
void WeaponCtrl::Shot()
{
	if (m_BulletCount <= 0) {
		return;
	}

	for (auto m : m_BulletList) {
		if (m->GetActive() == false)
		{
			m->GetComponent<MissileCtrl>()->Fire(&m_ParentTrans->position, m_ParentTrans->quaternion);
			m_BulletCount--;
			break;
		}
	}
}

/**
 * @brief 玉の発射
 * @return なし
 */
void WeaponCtrl::Shot(Quaternion quat)
{
	if (m_BulletCount <= 0) {
		return;
	}

	for (auto m : m_BulletList) {
		if (m->GetActive() == false)
		{
			m->GetComponent<MissileCtrl>()->Fire(&m_ParentTrans->position, quat);
			 m_BulletCount--;
			 break;
		}
	}
}

/**
 * @brief 玉の発射
 * @return なし
 */
void WeaponCtrl::Shot(Quaternion quat, GameObject * target)
{
	if (m_BulletCount <= 0) {
		return;
	}

	for (auto m : m_BulletList) {
		if (m->GetActive() == false)
		{
			m->GetComponent<MissileCtrl>()->Fire(&m_ParentTrans->position, quat, target);
			m_BulletCount--;
			break;
		}
	}
}


/**
 * @brief 玉の発射
 * @return なし
 */
void WeaponCtrl::Shot(GameObject * target)
{
	if (m_BulletCount <= 0) {
		return;
	}

	for (auto m : m_BulletList) {
		if (m->GetActive() == false)
		{
			m->GetComponent<MissileCtrl>()->Fire(&m_ParentTrans->position, m_ParentTrans->quaternion, target);
			m_BulletCount--;
			break;
		}
	}
}

// EOF