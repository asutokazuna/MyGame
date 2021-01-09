/**
 * @file PlayerShotDir.h
 * @brief プレイヤーの玉の発射方向を判定する
 */
#pragma once
#include "Component.h"
#include "MyMath.h"
#include <list>

class Transform;

/**
 * @class PlayerShotDir
 */
class PlayerShotDir:public Component
{
private:
	std::list<GameObject*> m_objlist;
	GameObject* m_target;		//!< 当たっている敵
	Vector3 m_target2DPos;
	GameObject* m_Lockon;

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT Init();
	
	/**
	 * @brief 更新処理
	 * @return　なし
	 */
	void LateUpdate();

	void Draw();

	/**
	 * @brief 当たっている敵の取得
	 * @return 当たっている敵
	 */
	GameObject* GetTarget();

	/**
	 * @brief 当たり判定処理
	 * @return なし
	 */
	void OnCollisionEnter(GameObject* other);
};

