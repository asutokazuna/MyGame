/**
 * @file Transform.h
 * @brief 座標管理クラス
 */
#include "Transform.h"
#include "Tween.h"

/**
 * @brief コンストラクタ
 */
Transform::Transform()
{
	Do = new Tween();

	position = { 0,0,0 };
	rotation = { 0,0,0 };
	scale = { 1,1,1 };
	localPosition = { 0,0,0 };
	localRotation = { 0,0,0 };
	localScale = { 1,1,1 };
	axisX = { 1,0,0 };
	axisY = { 0,1,0 };
	axisZ = { 0,0,1 };
	quaternion = { 1,0,0,0 };
}

Transform::Transform(const Transform & trans)
{

	Do = new Tween();
	*Do = *trans.Do;
	position = trans.position;
	rotation = trans.rotation;
	scale = trans.scale;
	localPosition = trans.localPosition;
	localRotation = trans.localRotation;
	localScale = trans.localScale;
	axisX = trans.axisX;
	axisY = trans.axisY;
	axisZ = trans.axisZ;
	quaternion = trans.quaternion;
}

Transform::~Transform()
{
	delete Do;
	Do = nullptr;
}

/**
 * @brief 座標の取得
 * @return 座標
 */
Vector3 Transform::GetPosition() 
{
	return position;
}

/**
 * @brief 回転の取得
 * @return 回転
 */
Vector3 Transform::GetRotation()
{
	return rotation;
}

/**
 * @brief 大きさの取得
 * @return 大きさ
 */
Vector3 Transform::GetScale()
{
	return scale;
}

/**
 * @brief 前方向の取得
 * @return 前方向
 */
Vector3 Transform::GetForward()
{
	Vector3 forward = {0,0,1};

	forward = MyMath::PosxQuaternion(forward, quaternion);

	return forward;
}

/**
 * @brief 右方向の取得
 * @return 右方向
 */
Vector3 Transform::GetRight()
{
	Vector3 right = { 1,0,0 };

	right = MyMath::PosxQuaternion(right, quaternion);

	return right;
}

/**
 * @brief 回転させる
 * @param[in]	kind 回転させる軸
 * @param[in]	rad	回転させる角度(ラジアン)
 * @return 実体
 */
Transform& Transform::AngleAxis(AxisKind kind, float rad)
{
	Vector3 axis = { 1,0,0 };

	// 軸を決める
	switch (kind)
	{
	case Transform::AXIS_X:
		axis = axisX;
		break;
	case Transform::AXIS_Y:
		axis = axisY;
		break;
	case Transform::AXIS_Z:
		rotation.z += rad;
		axis = axisZ;
		break;
	case Transform::AXIS_WORLD_X:
		axis = { 1,0,0 };
		break;
	case Transform::AXIS_WORLD_Y:
		axis = { 0,1,0 };
		break;
	case Transform::AXIS_WORLD_Z:
		axis = { 0,0,1 };
		break;
	default:
		break;
	}

	axisX = MyMath::RotateQuaternionPosition(axis, axisX, rad);
	axisY = MyMath::RotateQuaternionPosition(axis, axisY, rad);
	axisZ = MyMath::RotateQuaternionPosition(axis, axisZ, rad);

	quaternion = MyMath::AnglexQuaternion(quaternion, axis, rad);

	return *this;
}

// EOF