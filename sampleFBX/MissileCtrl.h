/**
 * @file MissileCtrl
 * @brief ’e‚Ì§ŒäƒRƒ“ƒ|[ƒlƒ“ƒg
 */
#pragma once
#include "Component.h"

/**
 * @class MissileCtrl
 * @brief ’e‚Ì§Œä
 */
class MissileCtrl :public Component
{
protected:
	int m_power;		//!< ’e‚ÌˆĞ—Í

public:
	/**
	 * @brief ‰Šú‰»ˆ—
	 * @return ‚È‚µ
	 */
	virtual void Awake();

	/**
	 * ’e‚ÌˆĞ—Í‚Ìæ“¾
	 * @return ’e‚ÌˆĞ—Í
	 */
	virtual int GetPower();
};

// EOF