/**
 * @file CoreGaugeUI
 * @brief �R�A��HP�Q�[�W�\��UI�I�u�W�F�N�g
 */
#include "CoreGaugeUI.h"
#include "GaugeUI.h"
#include "UIMesh.h"
#include "CorePlayerGauge.h"
#include "CoreEnemyGauge.h"

/**
 * @breif ����������
 * @return �Ȃ�
 */
void CoreGaugeUI::Awake()
{
	GameObject* playerCoreUI = new GaugeUI();
	playerCoreUI->SetName("PlayerCoreUI");
	SetChild(playerCoreUI);
	playerCoreUI->AddComponent<CorePlayerGauge>();
	GameObject* enemyCoreUI = new GaugeUI();
	playerCoreUI->SetName("EnemyCoreUI");
	SetChild(enemyCoreUI);
	enemyCoreUI->AddComponent<CoreEnemyGauge>();
	//BG�p
	//AddComponent<UIMesh>();
}

// EOF