/**
 * @file MissileCtrl
 * @brief ’e‚Ì§Œä
 */
#include "MissileCtrl.h"

/**
 * @brief ‰Šú‰»ˆ—
 * @return ‚È‚µ
 */
void MissileCtrl::Awake()
{
	m_power = 1;
}

/**
 * ’e‚ÌˆĞ—Í‚Ìæ“¾
 * @return ’e‚ÌˆĞ—Í
 */
int MissileCtrl::GetPower()
{
	return m_power;
}

// EOF