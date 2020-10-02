/**
 * @file PlayerMove
 * @brief プレイヤーの移動
 */
#pragma once
#include "Component.h"

// 前方宣言
class Transform;
class Rigidbody;

/**
 * @class PlayerMove
 * @brief プレイヤーの移動
 */
class PlayerMove: public Component
{
private:
	Transform* m_Transform;
	Rigidbody* rb;
public:

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT Init();

	/**
	 * @brief 更新処理
	 * @return なし
	 */
	void Update();
};

// EOF