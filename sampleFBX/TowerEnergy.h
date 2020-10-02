/**
 * @file TowerEnergy
 * @brief TowerEnergyクラス
 */
#pragma once
#include "Component.h"

// def
#define ENERGY_MAX (40)

// 前方宣言
class GameObject;

/**
 * @class TowerEnergy
 * @brief タワーのパラメーター
 */
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
	void Draw();
	void AddEnergy(int num);
	int GetEnergy();
	virtual void OnCollisionEnter(GameObject* othor);

};

