/**
 * @file Weapon
 * @brief 武器クラス
 */
#include "Weapon.h"
#include "Missile.h"
#include "WeaponCtrl.h"
//
///**
// * @brief コンストラクタ
// */
//Weapon::Weapon(int num):m_BulletMax(num){}

/**
 * @brief 初期化処理
 * @return なし
 */
void Weapon::Awake()
{
	//transform = &parent->GetTransform();
	//for (int i = 0; i < m_BulletMax; i++)
	//{
	//	Missile* temp = new Missile();
	//	m_BulletList.push_back(temp);
	//	SetChild(temp);
	//}

	AddComponent<WeaponCtrl>();
}

// EOF