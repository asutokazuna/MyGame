/**
 * @file Transform.h
 * @brief ���W�Ǘ��N���X
 */
#include "Transform.h"

/**
 * @brief �R���X�g���N�^
 */
Transform::Transform()
{
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

/**
 * @brief ���W�̎擾
 * @return ���W
 */
Vector3 Transform::GetPosition() 
{
	return position;
}

/**
 * @brief ��]�̎擾
 * @return ��]
 */
Vector3 Transform::GetRotation()
{
	return rotation;
}

/**
 * @brief �傫���̎擾
 * @return �傫��
 */
Vector3 Transform::GetScale()
{
	return scale;
}

/**
 * @brief �O�����̎擾
 * @return �O����
 */
Vector3 Transform::GetForward()
{
	Vector3 forward = {0,0,1};

	forward = MyMath::PosxQuaternion(forward, quaternion);

	return forward;
}

/**
 * @brief ��]������
 * @param[in]	kind ��]�����鎲
 * @param[in]	rad	��]������p�x(���W�A��)
 * @return ����
 */
Transform& Transform::AngleAxis(AxisKind kind, float rad)
{
	Vector3 axis = { 1,0,0 };

	// �������߂�
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