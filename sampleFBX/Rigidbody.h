/**
 * @file Rigidbody
 * @brief 物理挙動
 * @author Ariga
 */
#pragma once
#include "Component.h"
#include "MyMath.h"

// 前方宣言
class Transform;
class Collision;

/**
 * @class Rigidbody
 * @brief 物理演算を作りたかったが考えがまとまっていないので未完成
 */
class Rigidbody: public Component
{
private:
	static float	gravity;	//!< 重力
	float	mass;		//!< 質量
	Vector3 force;		//!< 力
	Vector3 subforce;		//!< 力
	Transform* parentTrans;		//!< 親のトランスフォーム
	float oldPosY;
	Collision* m_col;
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
	 * @brief 物体に力を加える
	 * @param[in]	force	加える力
	 * @return なし
	 */
	void AddForce(Vector3 force);

};

// EOF