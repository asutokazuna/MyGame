/**
 * @file PlayerCtrl
 * @brief プレイヤーの制御クラス
 */
#pragma once
#include "Component.h"
#include <list>
#include <memory>

 // 前方宣言
class Transform;
class Weapon;

/**
 * @class PlayerCtrl
 * @brief プレイヤーの詳細な制御
 */
class PlayerCtrl: public Component
{
private:
	Weapon* m_Weapon;
	Transform* m_ParentTrans;				//!< 親の座標など

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 更新処理
	 * @return なし
	 */
	void Update();
	void Attak();
};

// EOF