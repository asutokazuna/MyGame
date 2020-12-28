/**
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
	unsigned int m_Life;		//!< HP
	NumberList* m_numberUI;

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

	void  OnCollisionEnter(GameObject* gameObbj);
	/**
	 * @brief HPの取得
	 * @return 現在HPの取得
	 */
	unsigned int GetLife();
};

// EOF