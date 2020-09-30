/**
 * @file TowerManager
 * @brief タワー管理クラス
 */
#include "TowerManager.h"
#include "Tower.h"
#include "TowerEnergy.h"
#include "collision.h"

#define MAX_TOWER (3)
#define POS_OFFSET_X (300)

int TowerManager::m_isAttack = 0;

TowerManager::TowerManager()
{
	m_Tower = new Tower[3];
}

TowerManager::~TowerManager()
{
	delete[] m_Tower;
}

void TowerManager::Awake()
{
	for (int i = 0; i < MAX_TOWER; i++)
	{
		m_Tower[i].Awake();
	}
}

HRESULT TowerManager::Init()
{
	for (int i = 0; i < MAX_TOWER; i++) 
	{
		m_Tower[i].Init();
	}

	Vector3 pos = { -POS_OFFSET_X,0,0 };
	for (int i = 0; i < MAX_TOWER; i++)
	{
		m_Tower[i].SetPos(pos);
		pos.x += POS_OFFSET_X;
	}
	return S_OK;
}

void TowerManager::Uninit()
{
	for (int i = 0; i < MAX_TOWER; i++)
	{
		m_Tower[i].Uninit();
	}
}

void TowerManager::Update()
{
	for (int i = 0; i < MAX_TOWER; i++)
	{
		m_Tower[i].Update();
	}
	IsAttackPlayerCore();
	IsAttackEnemyCpre();
}

void TowerManager::Draw()
{
	for (int i = 0; i < MAX_TOWER; i++)
	{
		m_Tower[i].Draw();
	}
}

void TowerManager::DrawAlpha()
{
	for (int i = 0; i < MAX_TOWER; i++)
	{
		m_Tower[i].DrawAlpha();
	}
}

bool TowerManager::IsAttackPlayerCore()
{
	int cnt = 0;
	for (int i = 0; i < MAX_TOWER; i++)
	{
		if (m_Tower[i].m_Energy->GetEnergy() <= 0) {
			cnt++;
		}
	}
	if (cnt >= 2) {
		m_isAttack = Collision::COL_CORE_PLAYER;
		return true;
	}

	return false;
}

bool TowerManager::IsAttackEnemyCpre()
{
	int cnt = 0;
	for (int i = 0; i < MAX_TOWER; i++)
	{
		if (m_Tower[i].m_Energy->GetEnergy() >= ENERGY_MAX) {
			cnt++;
		}
	}
	if (cnt >= 2) {
		m_isAttack = Collision::COL_CORE_ENEMY;
		return true;
	}
	return false;
}

// EOF