/**
 * @file　WeaponBulletCount
 * @brief 武器の残り残弾数の表示コンポーネント
 */
#pragma once
#include "Component.h"

// 前方宣言
class WeaponCtrl;

/**
 * @class WeaponBulletCount
 * @brief 武器の残り残弾数の表示コンポーネント
 */
class WeaponBulletCount: public Component
{
private:
	GameObject* m_BulletNum;	//!< 弾数表示UIオブジェクト
	WeaponCtrl* WeapCtrl;		//!< 武器管理コンポーネント(弾数取得用)

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT Init();

	/**
	 * @brief 更新処理
	 * @return なし
	 */
	void Update();
};

// EOF