/**
 * @file Weapon
 * @brief 武器クラス
 */
#pragma once
#include "GameObject.h"
#include <list>

// 前方宣言
class Missile;

/**
 * @class Weapon
 * @brief 武器
 */
class Weapon :public GameObject
{
private:
	std::list<Missile*> m_BulletList;
	int m_BulletMax;

public:
	///**
	// * @brief コンストラクタ
	// */
	//Weapon(int num);

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	virtual void Awake();

};

// EOF