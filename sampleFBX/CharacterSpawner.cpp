/**
 * @file CharacterSpawner
 * @brief キャラの生成管理オブジェクト
 */
#include "CharacterSpawner.h"
#include "CharacterSpawnCtrl.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void CharacterSpawner::Awake()
{
	AddComponent<CharacterSpawnCtrl>();
}

// EOF