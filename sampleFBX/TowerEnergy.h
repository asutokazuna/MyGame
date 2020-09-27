/**
 * @file TowerEnergy
 * @brief TowerEnergyƒNƒ‰ƒX
 */
#pragma once
#include "Component.h"

#define ENERGY_MAX (40)

class TowerEnergy :public Component
{
public:
	enum ENERGY_TYPE
	{
		ENERGY_PLAYER,
		ENERGY_ENEMY
	};
private:
	int m_Energy;
	int id;
public:
	TowerEnergy();
	~TowerEnergy();
	void Draw();
	void AddEnergy(int num);
	int GetEnergy();
};

