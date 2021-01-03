/**
 * @file Transform.h
 * @brief 座標管理クラス
 */
#pragma once
#include "Component.h"
#include "MyMath.h"
#include "Tween.h"

class Tween;

/**
 * @class Transform
 * @brief 座標管理クラス
 */
class Transform : public Component
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Vector3 localPosition;
	Vector3 localRotation;
	Vector3 localScale;
	Vector3 axisX;
	Vector3 axisY;
	Vector3 axisZ;
	Quaternion quaternion;

public:
	Tween* Do;

	Transform& operator= (const Transform trs) {
		position = trs.position;
		rotation = trs.rotation;
		scale = trs.scale;
		localPosition = trs.localPosition;
		localRotation = trs.localRotation;
		localScale = trs.localScale;
		axisX = trs.axisX;
		axisY = trs.axisY;
		axisZ = trs.axisZ;
		quaternion = trs.quaternion;
		*(Do) = *(trs.Do);
		//Tween t;
		//t = *trs.Do;
		return *this;
	}
	/**
	 * @brief コンストラクタ
	 */
	Transform();
	/**
	* @brief コンストラクタ
	*/
	Transform(const Transform &trans);

	/**
	 * @brrief デストラクタ
	 */
	~Transform();

	/**
	 * @brief 座標の取得
	 * @return 座標
	 */
	Vector3 GetPosition();

	/**
	 * @brief 回転の取得
	 * @return 回転
	 */
	Vector3 GetRotation();

	/**
	 * @brief 大きさの取得
	 * @return 大きさ
	 */
	Vector3 GetScale();

	/**
	 * @brief 前方向の取得
	 * @return 前方向
	 */
	Vector3 GetForward();

	Vector3 GetRight();

	Vector3 GetUp();

	enum AxisKind
	{
		AXIS_X,
		AXIS_Y,
		AXIS_Z,
		AXIS_WORLD_X,
		AXIS_WORLD_Y,
		AXIS_WORLD_Z,
	};

	/**
	 * @brief 回転させる
	 * @param[in]	kind 回転させる軸
	 * @param[in]	rad	回転させる角度(ラジアン)
	 * @return 実体
	 */
	Transform& AngleAxis(AxisKind kind, float rad);
};

// EOF