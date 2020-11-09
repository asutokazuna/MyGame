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
	Transform* m_Transform;		//!< 座標
	Rigidbody* rb;
	POINT angle;			//!< 回転角度
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

	/**
	 * @brief 高速移動
	 *@return なし
	 */
	void FullDrive();

	/**
	 * @brief 視点移動
	 * @return なし
	 */
	void Rotate();

	/**
	 * @brief 当たり判定処理
	 * @return なし
	 */
	void OnCollisionEnter(GameObject* gameObbj);
};

// EOF