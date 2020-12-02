/**
 * @file PlayerMove
 * @brief プレイヤーの移動
 */
#pragma once
#include "Component.h"
#include "MyMath.h"

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
	Vector3 m_move;			//!< 移動量
	bool m_isDelay;			//!< ディレイ
	int m_delayTime;

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

	void LateUpdate();

	void Draw();

	/**
	 * @brief 高速移動
	 *@return なし
	 */
	void FullDrive();

	void Avoid();

	/**
	 * @brief 視点移動
	 * @return なし
	 */
	void Rotate();
	
	/**
	 * @brief 移動量のセット
	 * @return なし
	 */
	void SetMove(Vector3 move);

	/**
	 * @brief 移動量のセット
	 * @return なし
	 */
	void SetMove(Vector3 move, Quaternion quat);

		
	/**
	 * @brief 移動量の加算
	 * @return なし
	 */
	void AddMove(Vector3 move);
	
	/**
	 * @brief 移動量の加算
	 * @return なし
	 */
	void AddMove(Vector3 move, Quaternion quat);

	/**
	 * @brief 当たり判定処理
	 * @return なし
	 */
	void OnCollisionEnter(GameObject* gameObbj);
};

// EOF