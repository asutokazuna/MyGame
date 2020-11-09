/**
 * @file EnemyCtrl
 * @brief 敵の動きクラス
 */
#include "EnemyCtrl.h"
#include "GameObject.h"
#include "Weapon.h"
#include "WeaponCtrl.h"

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT EnemyCtrl::Init()
{
	m_transform = &m_Parent->GetTransform();
	m_transform->position.z = 500;
	m_transform->AngleAxis(Transform::AXIS_Y, MyMath::AngleToRadian(180));

	m_Weapon = m_Parent->GetChild<Weapon>();

	return E_NOTIMPL;
}

void EnemyCtrl::Update()
{
	//m_transform->position += m_transform->GetForward();

	static int time = 0;
	time++;

	if (time >= 60)
	{
		time = 0;
		m_Weapon->GetComponent<WeaponCtrl>()->Shot();
	}
}

// EOF