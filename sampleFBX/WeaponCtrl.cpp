/**
 * @file WeaponCtrl
 * @brief 武器の制御クラス
 */
#include "WeaponCtrl.h"
#include "Transform.h"
#include "Missile.h"
#include "GameObject.h"


/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT WeaponCtrl::Init()
{
	m_BulletList = m_Parent->GetChildren<Missile>();
	m_ParentTrans = &m_Parent->GetTransform();
	m_BulletCount = m_BulletList.size();

	m_DelayTime = 60;
	return E_NOTIMPL;
}

void WeaponCtrl::Update()
{
	if (m_BulletCount <= 0) {
		m_DelayTime--;
	}
	if (m_DelayTime < 0) {
		m_BulletCount = m_BulletList.size();
		m_DelayTime = 60;
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
		bool flg = false;
		flg = m->Fire(&m_ParentTrans->position, m_ParentTrans->quaternion);
		if (flg == true) {
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
		bool flg = false;
		flg = m->Fire(&m_ParentTrans->position, quat);
		if (flg == true) {
			m_BulletCount--;
			break;
		}
	}
}


// EOF