/**
 * @class EnemyLifeCtrl
 * @brief 敵のHPの管理コンポーネント
 */
#pragma once
#include "Component.h"

/**
 * @class EnemyLifeCtrl
 * @brief 敵のHPの管理コンポーネント
 */
class EnemyLifeCtrl :public Component
{
private:
	int m_Life;		//!< HP
public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT Init();

	/**
	 * @brief 当たった時の処理
	 * @return なし
	 */
	void  OnCollisionEnter(GameObject* gameObj);
	/**
	 * @brief HPの取得
	 * @return 現在HPの取得
	 */
	int GetLife();
	float GetLifePercent();
};

// EOF