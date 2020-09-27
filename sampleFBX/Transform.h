/**
 * @file Transform.h
 * @brief 座標管理クラス
 */
#pragma once
#include "Component.h"
#include "MyMath.h"

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
	Vector3 worldPosition;
	Vector3 worldRotation;
	Vector3 worldScale;
	Vector3 axisX;
	Vector3 axisY;
	Vector3 axisZ;
	Quaternion quaternion;

	Transform();

	Vector3 GetPosition();

	Vector3 GetRotation();

	Vector3 GetScale();

	Vector3 GetForward();

	enum AxisKind
	{
		AXIS_X,
		AXIS_Y,
		AXIS_Z,
		AXIS_WORLD_X,
		AXIS_WORLD_Y,
		AXIS_WORLD_Z,
	};

	Transform& AngleAxis(AxisKind kind, float rad);
};

// EOF