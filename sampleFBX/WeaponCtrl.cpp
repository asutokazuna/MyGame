/**
 * @file WeaponCtrl
 * @brief 武器の制御コンポーネント
 */
#include "WeaponCtrl.h"
#include "Transform.h"
#include "Missile.h"
#include "GameObject.h"
#include "MissileCtrl.h"
#include "ObjectManager.h"

/**
 * @brief コンストラクタ
 */
WeaponCtrl::WeaponCtrl():m_BulletCount(0), m_ReloadTime(60), m_maxBullet(0)
{
}

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT WeaponCtrl::Init()
{
	m_ReloadTime = 60;

	return E_NOTIMPL;
}

/**
 * @brief 更新処理
 * @return なし
 */
void WeaponCtrl::Update()
{
	*m_ParentTransform = m_Parent->GetParent()->GetTransform();
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

	int cnt = 0;
	for (auto m : m_BulletList) 
	{
		if (m->GetActive() == false)
		{
			m->GetComponent<MissileCtrl>()->Fire(&m_ParentTransform->position, m_ParentTransform->quaternion);
			m_BulletCount--;
			break;
		}
		cnt++;
		if (m_maxBullet <= cnt) {
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

	int cnt = 0;
	for (auto m : m_BulletList) 
	{
		if (m->GetActive() == false)
		{
			m->GetComponent<MissileCtrl>()->Fire(&m_ParentTransform->position, quat);
			 m_BulletCount--;
			 break;
		}
		cnt++;
		if (m_maxBullet <= cnt) {
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

	int cnt = 0;
	for (auto m : m_BulletList) 
	{
		if (m->GetActive() == false)
		{
			m->GetComponent<MissileCtrl>()->Fire(&m_ParentTransform->position, quat, target);
			m_BulletCount--;
			break;
		}
		cnt++;
		if (m_maxBullet <= cnt) {
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

	int cnt = 0;
	for (auto m : m_BulletList) 
	{
		if (m->GetActive() == false)
		{
			m->GetComponent<MissileCtrl>()->Fire(&m_ParentTransform->position, m_ParentTransform->quaternion, target);
			m_BulletCount--;
			break;
		}
		cnt++;
		if (m_maxBullet <= cnt) {
			break;
		}
	}
}

/**
 * @brief 弾の最大数の設定
 * @param[in] num 発射できる弾の最大数
 * @return なし
 */
void WeaponCtrl::SetMaxBullet(int num) 
{
	m_maxBullet = m_BulletCount = num;
	int cnt = m_maxBullet - (int)m_BulletList.size();
	for (int i = 0; i < cnt; i++)
	{
		Missile* obj = ObjectManager::Create<Missile>("Missile");
		m_BulletList.push_back(obj);
	}
}

// EOF