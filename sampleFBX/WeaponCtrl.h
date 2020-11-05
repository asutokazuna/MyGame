/**
 * @file WeaponCtrl
 * @brief 武器の制御クラス
 */
#pragma once
#include "Component.h"

// 前方宣言
class Missile;
class Transform;

/**
 * @class WeaponCtrl
 * @brief 武器の制御
 */
class WeaponCtrl :public Component
{
private:
	std::list<Missile*> m_BulletList;	//!< ミサイルリスト
	Transform* m_ParentTrans;			//!< 親の座標

public:

	/**
	 * @brief 値の初期化
	 * @return なし
	 */
	void InitParam(std::list<Missile*>& missile);

	/**
	 * @brief 玉の発射
	 * @return なし
	 */
	void Shot();

	/**
	 * @brief 玉の発射
	 * @return なし
	 */
	void Shot(Transform* target);
};

// EOF