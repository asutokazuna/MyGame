/**
 * @file　WeaponBulletCount
 * @brief 武器の残り残弾数の表示コンポーネント
 */
#pragma once
#include "Component.h"

class NumberList;
class Missile;

class WeaponBulletCount: public Component
{
private:
	GameObject* m_BulletNum;
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