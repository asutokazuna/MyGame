/**
 * @file TowerManager
 * @brief タワー管理クラス
 */
#pragma once
#include "GameObject.h"
#include <list>

// 前方宣言
class Tower;

/**
 * @class TowerManager
 * @brief タワーの管理クラス
 */
class TowerManager: public GameObject
{
private:
	std::list<Tower*> m_Tower;		//!< タワー

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT Init();
};

// EOF