/**
 * @file TowerEnergy
 * @brief TowerEnergy�N���X
 */
#pragma once
#include "Component.h"

// def
#define ENERGY_MAX (40)

// �O���錾
class GameObject;

/**
 * @class TowerEnergy
 * @brief �^���[�̃p�����[�^�[
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

