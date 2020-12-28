/**
 * @file PlayerLifeUI
 * @brief HP‚Ì•\Ž¦
 */
#include "PlayerLifeUI.h"
#include "GameObject.h"
#include "PlayerLifeCtrl.h"
#include "NumberDrawer.h"

/**
 * @brief ‰Šú‰»ˆ—
 * @return ‚È‚µ
 */
void PlayerLifeUI::Awake()
{
	m_NumberList = m_Parent->GetChildren<GameObject>();
	m_lifeCtrl = m_Parent->GetParent()->GetComponent<PlayerLifeCtrl>();
}

/**
 * @brief XVˆ—
 * @return ‚È‚µ
 */
void PlayerLifeUI::Update()
{
	unsigned int num = m_lifeCtrl->GetLife();
	int work = num;
	int value = 0;

	for (auto obj : m_NumberList)
	{
		value = work % 10;
		obj->GetComponent<NumberDrawer>()->SetNumber(value);
		work /= 10;
	}
}

// EOF