/**
 * @file CharacterSpawner
 * @brief キャラの生成管理オブジェクト
 */
#include "CharacterSpawner.h"
#include "CharacterSpawnCtrl.h"

void CharacterSpawner::Awake()
{
	AddComponent<CharacterSpawnCtrl>();
}

// EOF