/**
 * @file
 */
#pragma once
#include "Component.h"
#include <list>

class DigitNumber;
class Missile;

class WeaponBulletCount: public Component
{
private:
	std::list<DigitNumber*> m_BulletNum;
public:
	HRESULT Init();
	void Update();
};

// EOF