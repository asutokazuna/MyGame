/**
 * @file CoreCollision
 * @brief CoreCollisionクラス
 */
#pragma once
#include "collision.h"

class CoreCollision :public Collision
{
protected:
	bool m_isInvincible;	//!< 無敵かどうか
	int m_OpponentBulletTag;	//!< ダメージ判定の相手の識別番号
	int m_OpponentTower;	//!< 相手のタワーの識別番号
public:
	CoreCollision();
	void Update();
	void OnCollisionEnter(GameObject* gameObj);
	void SetOpponentBullet(int kind);
	void SetOpponentTower(int kind);
};

// EOF