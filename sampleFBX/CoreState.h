/**
 * @file CoreState
 * @brief CoreState�R���|�[�l���g
 */
#pragma once
#include "Component.h"

/**
 * @file CoreState
 * @brief CoreState�N���X
 */
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
	float GetPercent();
};

// EOF