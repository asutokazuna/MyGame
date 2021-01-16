/**
 * @file CharacterSpawner
 * @brief キャラの生成管理コンポーネント
 */
#pragma once
#include "Component.h"
#include "GameObject.h"
#include <list>

#define SPAWN_TIME (60 * 2)

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
	
	/**
	 * @brief 終了処理
	 * @return なし
	 */
	virtual void Uninit();
	
	/**
	 * @brief 更新処理
	 * @return なし
	 */
	virtual void Update();
	
	/**
	 * @brief 生成待機しているか判定する
	 * @param[in] obj 判定したいオブジェクト
	 * @return 登録されていればtrue
	 */
	bool IsExistence(GameObject* obj);

	/**
	 * @brief 生成待機リストへセット
	 * @param[in] obj セットするオブジェクト
	 * @param[in] time 生成待機時間
	 * @return なし
	 */
	void Set(GameObject * obj, int time = SPAWN_TIME);
};

// EOF