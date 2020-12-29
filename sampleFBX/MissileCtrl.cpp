/**
 * @file MissileCtrl
 * @brief 弾の制御コンポーネント
 */
#include "MissileCtrl.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void MissileCtrl::Awake()
{
	m_power = 1;
}

/**
 * 弾の威力の取得
 * @return 弾の威力
 */
int MissileCtrl::GetPower()
{
	return m_power;
}

// EOF