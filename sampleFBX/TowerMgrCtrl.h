/**
 * @file TowerMgrCtrl
 * @brief タワー管理コンポーネント
 */
#pragma once
#include "Component.h"
#include <list>

#define MAX_TOWER (3)

class Tower;

/**
 * @class TowerMgrCtrl
 * @brief タワー管理コンポーネント
 */
class TowerMgrCtrl:public Component
{
private:
	std::list<GameObject*> m_towerList;

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	HRESULT Init();

	/**
	 * @brief 半分以上占拠しているか
	 * @return 半分以上占拠していればtrue
	 */
	bool IsOccupation(int kind);
};

// EOF