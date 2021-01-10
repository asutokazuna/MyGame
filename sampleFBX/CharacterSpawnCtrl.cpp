/**
 * @file CharacterSpawner
 * @brief キャラの生成管理オブジェクト
 */
#include "CharacterSpawnCtrl.h"

#define SPAWN_TIME (60 * 2)

void CharacterSpawnCtrl::Awake()
{
}

void CharacterSpawnCtrl::Uninit()
{
	m_charaList.clear();
}

void CharacterSpawnCtrl::Update()
{
	for (auto it = m_charaList.begin(); it != m_charaList.end(); )
	{
		it->time--;

		if (it->time <= 0)
		{
			it->object->SetActive(true);
			it->object->Init();
			it = m_charaList.erase(it);
		}
		else {
			it++;
		}
	}
}

void CharacterSpawnCtrl::Set(GameObject * obj)
{
	CharaData data;
	data.object = obj;
	data.time = SPAWN_TIME;
	m_charaList.push_back(data);
}
