/**
 * @file CharacterSpawner
 * @brief キャラの生成管理オブジェクト
 */
#include "CharacterSpawnCtrl.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void CharacterSpawnCtrl::Awake()
{
}

/**
 * @brief 終了処理
 * @return なし
 */
void CharacterSpawnCtrl::Uninit()
{
	m_charaList.clear();
}

/**
 * @brief 更新処理
 * @return なし
 */
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

/**
 * @brief 生成待機しているか判定する
 * @param[in] obj 判定したいオブジェクト
 * @return 登録されていればtrue
 */
bool CharacterSpawnCtrl::IsExistence(GameObject * obj)
{
	for (auto listObj : m_charaList)
	{
		if (listObj.object == obj)
		{
			return true;
		}
	}

	return false;
}

/**
 * @brief 生成待機リストへセット
 * @param[in] obj セットするオブジェクト
 * @param[in] time 生成待機時間
 * @return なし
 */
void CharacterSpawnCtrl::Set(GameObject * obj, int time)
{
	CharaData data;
	data.object = obj;
	data.time = time;
	m_charaList.push_back(data);
}

// EOF