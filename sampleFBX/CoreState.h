/**
 * @file CoreState
 * @brief CoreStateƒNƒ‰ƒX
 */
#pragma once
#include "Component.h"

class CoreState :public Component
{
private:
	int m_Life;
public:
	CoreState();
	void Draw();
	int GetLife();
	void AddLife(int value);
	void SetLife(int Life);
};

