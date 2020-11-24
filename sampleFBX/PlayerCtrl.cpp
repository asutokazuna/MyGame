/**
 * @file PlayerCtrl
 * @brief プレイヤーの制御クラス
 */
#include "PlayerCtrl.h"
#include "input.h"
#include "Transform.h"
#include "GameObject.h"
#include "Weapon.h"
#include "WeaponCtrl.h"
#include "Geometry.h"
#include "PlayerShotDir.h"
#include "PlayerMove.h"

#define WAIT_TIME (1 * 60)

/**
 * @brief 初期化処理
 * @return なし
 */
void PlayerCtrl::Awake()
{
	m_Weapon = m_Parent->GetChild<Weapon>();
}

/**
 * @brief 更新処理
 * @return なし
 */
void PlayerCtrl::Update()
{

}

void PlayerCtrl::Attak()
{
	Quaternion dir = m_Parent->GetTransform().quaternion;
	Cube* cube = m_Parent->GetChild<Cube>();
	GameObject* target = cube->GetComponent<PlayerShotDir>()->GetTarget();

	if (target != nullptr) {
		dir = MyMath::LookAt(m_Parent->GetTransform().position, target->GetTransform().position);
	}

	m_Weapon->GetComponent<WeaponCtrl>()->Shot(dir);	
}

// EOF