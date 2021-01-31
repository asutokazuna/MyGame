/**
 * @file CoreGaugeUI
 * @brief コアのHPゲージ表示UIオブジェクト
 */
#include "CoreGaugeUI.h"
#include "GaugeUI.h"
#include "UIMesh.h"
#include "CorePlayerGauge.h"
#include "CoreEnemyGauge.h"
#include "ObjectManager.h"

/**
 * @breif 初期化処理
 * @return なし
 */
void CoreGaugeUI::Awake()
{
	GameObject* playerCoreUI;
	playerCoreUI = ObjectManager::Create<GaugeUI>("PlayerCoreUI");
	playerCoreUI->SetName("PlayerCoreUI");
	SetChild(playerCoreUI);
	playerCoreUI->AddComponent<CorePlayerGauge>();
	GameObject* enemyCoreUI;
	enemyCoreUI = ObjectManager::Create<GaugeUI>("EnemyCoreUI");
	enemyCoreUI->SetName("EnemyCoreUI");
	SetChild(enemyCoreUI);
	enemyCoreUI->AddComponent<CoreEnemyGauge>();
	//BG用
	//AddComponent<UIMesh>();
}

// EOF