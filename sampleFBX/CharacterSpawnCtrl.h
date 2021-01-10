/**
 * @file CharacterSpawner
 * @brief キャラの生成管理コンポーネント
 */
#pragma once
#include "Component.h"
#include "GameObject.h"
#include <list>

struct CharaData
{
	GameObject* object;
	int time;
};

/**
 * @file CharacterSpawner
 * @brief キャラの生成管理コンポーネント
 */
class CharacterSpawnCtrl :public Component
{
protected:
	std::list<CharaData> m_charaList;
public:
	void Awake();

	void Uninit();

	void Update();

	void Set(GameObject* obj);
};

// EOF