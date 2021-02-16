/**
 * @class PlayerLifeCtrl
 * @brief プレイヤーのHPの管理
 */
#pragma once
#include "Component.h"

// 前方宣言
class NumberList;


#define MAX_LIFE (10)	//!< プレイヤーの最大ライフ

/**
 * @class PlayerLifeCtrl
 * @brief プレイヤーのHPの管理
 */
class PlayerLifeCtrl :public Component
{
private:
	int m_Life;		//!< HP

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

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
};

// EOF