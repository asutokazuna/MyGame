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
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	virtual void Awake();

	virtual void Uninit();

	virtual void Update();

	virtual void Set(GameObject* obj);
};

// EOF