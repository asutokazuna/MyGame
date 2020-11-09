/**
 * @file EnemyCtrl
 * @brief 敵の動きクラス
 */
#pragma once
#include "Component.h"

// 前方宣言
class Transform;
class Weapon;

/**
 * @class EnemyCtrl 
 * @brief 敵の動きを制御するクラス
 */
class EnemyCtrl :public Component
{
private:
	Transform* m_transform;		// 親のトランスフォーム
	Weapon* m_Weapon;

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT Init();
	void Update();
};

// EOF