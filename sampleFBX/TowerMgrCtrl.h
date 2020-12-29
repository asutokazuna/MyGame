/**
 * @file TowerMgrCtrl
 * @brief �^���[�Ǘ��R���|�[�l���g
 */
#pragma once
#include "Component.h"
#include <list>

#define MAX_TOWER (3)

class Tower;

/**
 * @class TowerMgrCtrl
 * @brief �^���[�Ǘ��R���|�[�l���g
 */
class TowerMgrCtrl:public Component
{
private:
	std::list<Tower*> m_towerList;

public:
	/**
	 * @brief ����������
	 * @return �Ȃ�
	 */
	void Awake();

	/**
	 * @brief �����ȏ�苒���Ă��邩
	 * @return �����ȏ�苒���Ă����true
	 */
	bool IsOccupation(int kind);
};

// EOF