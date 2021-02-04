/**
 * @file TowerManager
 * @brief タワー管理クラス
 */
#include "TowerManager.h"
#include "Tower.h"
#include "TowerEnergy.h"
#include "collision.h"
#include "TowerMgrCtrl.h"
#include "ObjectManager.h"

// @def
#define POS_OFFSET_X (500)

/**
 * @brief 初期化処理
 * @return なし
 */
void TowerManager::Awake()
{
	for (int i = 0; i < MAX_TOWER; i++)
	{
		Tower* temp = //new Tower();
		ObjectManager::Create<Tower>("Tower");
		m_Tower.push_back(temp);
		temp->SetParent(this);
	}
	AddComponent<TowerMgrCtrl>();
}

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT TowerManager::Init()
{
	for (auto t : m_Tower)
	{
		t->Init();
	}

	Vector3 pos = { -POS_OFFSET_X,0,0 };
	for (auto t: m_Tower)
	{
		t->GetTransform().position = pos;
		pos.x += POS_OFFSET_X;
	}

	return S_OK;
}

// EOF