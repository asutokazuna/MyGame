/**
 * @file TowerMgrCtrl
 * @brief タワー管理コンポーネント
 * @author Ariga
 */
#include "TowerMgrCtrl.h"
#include "GameObject.h"
#include "Tower.h"
#include "TowerCtrl.h"
#include "ObjectManager.h"
#include "collision.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void TowerMgrCtrl::Awake()
{
	//m_towerList = m_Parent->GetChildren<Tower>();
}

HRESULT TowerMgrCtrl::Init()
{
	m_towerList = ObjectManager::GetInstance().FindObjectsWithTag(OBJ_TAG_TOWER);

	return S_OK;
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