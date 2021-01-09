/**
 * @file TowerMgrCtrl
 * @brief タワー管理コンポーネント
 */
#include "TowerMgrCtrl.h"
#include "GameObject.h"
#include "Tower.h"
#include "TowerCtrl.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void TowerMgrCtrl::Awake()
{
	m_towerList = m_Parent->GetChildren<Tower>();
}

/**
 * @brief 半分以上占拠しているか
 * @return 半分以上占拠していればfalse
 */
bool TowerMgrCtrl::IsOccupation(int kind)
{
	int cnt = 0;
	int haltCnt = (int)((float)MAX_TOWER / 2 + 0.5f);

	if (TowerCtrl::TOWERSTATE::NONE == kind) {
		return true;
	}

	for (auto obj : m_towerList)
	{
		if (kind == obj->GetComponent<TowerCtrl>()->GetState())
		{
			cnt++;
		}
	}
	if (haltCnt <= cnt) {
		return false;
	}

	return true;
}

// EOF