﻿/**
 * @class PlayerLifeCtrl
 * @brief プレイヤーのHPの管理
 */
#pragma once
#include "Component.h"

class NumberList;

/**
 * @class PlayerLifeCtrl
 * @brief プレイヤーのHPの管理
 */
class PlayerLifeCtrl :public Component
{
private:
	int m_Life;		//!< HP
	GameObject* m_numberUI;
	GameObject* m_gauge;
public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	HRESULT Init();

	/**
	 * @brief 更新処理
	 * @return なし
	 */
	void Update();

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