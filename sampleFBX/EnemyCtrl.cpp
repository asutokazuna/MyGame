/**
 * @file EnemyCtrl
 * @brief 敵の動きクラス
 */
#include "EnemyCtrl.h"
#include "GameObject.h"
#include "Weapon.h"
#include "WeaponCtrl.h"
#include "ObjectManager.h"
#include <list>
#include "collision.h"
#include "TowerCtrl.h"

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT EnemyCtrl::Init()
{
	m_transform = &m_Parent->GetTransform();
	m_transform->position = Vector3(0, 0, 500);
	m_transform->quaternion = Quaternion(1,0,0,0);
	m_transform->AngleAxis(Transform::AXIS_Y, MyMath::AngleToRadian(180));

	m_Weapon = m_Parent->GetChild<Weapon>();

	return E_NOTIMPL;
}

/**
 * @brief 更新処理
 * @return なし
 */
void EnemyCtrl::Update()
{
	//m_transform->position += m_transform->GetForward();

	static int time = 0;
	time++;

	if (time >= 60)
	{
		time = 0;
		
	}
}

/**
 * @breif target位置へ移動
 * @return なし
 */
void EnemyCtrl::Move(Vector3 target)
{
	Vector3 vec = target - m_transform->position;

	MyMath::Normalize(vec);

	m_transform->position += vec;
}

/**
 * @brief プレイヤーが占拠しているタワーへ移動
 * @return なし
 */
void EnemyCtrl::GotoPlayerTower()
{
	std::list<GameObject*> towerList = ObjectManager::GetInstance().FindObjectsWithTag(OBJ_TAG_TOWER);

	for (auto obj : towerList)
	{
		if (obj->GetComponent<TowerCtrl>()->GetState() == TowerCtrl::TOWERSTATE::PLAYER)
		{
			Move(obj->GetTransform().position);
			break;
		}
	}
}

/**
 * @brief 占拠されていないタワーへ移動
 * @return なし
 */
void EnemyCtrl::GotoNoneTower()
{
	std::list<GameObject*> towerList = ObjectManager::GetInstance().FindObjectsWithTag(OBJ_TAG_TOWER);

	for (auto obj : towerList)
	{
		if (obj->GetComponent<TowerCtrl>()->GetState() == TowerCtrl::TOWERSTATE::NONE)
		{
			Move(obj->GetTransform().position);
			break;
		}
	}
}

void EnemyCtrl::GotoCore()
{
}

/**
 * @brief 正面の方向へ攻撃
 * @return なし
 */
void EnemyCtrl::Attack()
{
	m_Weapon->GetComponent<WeaponCtrl>()->Shot();
}

// EOF