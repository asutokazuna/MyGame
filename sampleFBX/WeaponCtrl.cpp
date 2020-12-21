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

	return E_NOTIMPL;
}

/**
* @brief 玉の発射
* @return なし
*/
void WeaponCtrl::Shot()
{
	for (auto m : m_BulletList) {
		bool flg = false;
		flg = m->Fire(&m_ParentTrans->position, m_ParentTrans->quaternion);
		if (flg == true) {
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
	for (auto m : m_BulletList) {
		bool flg = false;
		flg = m->Fire(&m_ParentTrans->position, quat);
		if (flg == true) {
			break;
		}
	}
}


// EOF