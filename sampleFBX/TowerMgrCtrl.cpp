/**
 * @file TowerMgrCtrl
 * @brief �^���[�Ǘ��R���|�[�l���g
 */
#include "TowerMgrCtrl.h"
#include "GameObject.h"
#include "Tower.h"
#include "TowerCtrl.h"

/**
 * @brief ����������
 * @return �Ȃ�
 */
void TowerMgrCtrl::Awake()
{
	m_towerList = m_Parent->GetChildren<Tower>();
}

/**
 * @brief �����ȏ�苒���Ă��邩
 * @return �����ȏ�苒���Ă����false
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