/**
 * @file Transform.h
 * @brief ���W�Ǘ��N���X
 */
#pragma once
#include "Component.h"
#include "MyMath.h"

/**
 * @class Transform
 * @brief ���W�Ǘ��N���X
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
	/**
	 * @brief �R���X�g���N�^
	 */
	Transform();

	/**
	 * @brief ���W�̎擾
	 * @return ���W
	 */
	Vector3 GetPosition();

	/**
	 * @brief ��]�̎擾
	 * @return ��]
	 */
	Vector3 GetRotation();

	/**
	 * @brief �傫���̎擾
	 * @return �傫��
	 */
	Vector3 GetScale();

	/**
	 * @brief �O�����̎擾
	 * @return �O����
	 */
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

	/**
	 * @brief ��]������
	 * @param[in]	kind ��]�����鎲
	 * @param[in]	rad	��]������p�x(���W�A��)
	 * @return ����
	 */
	Transform& AngleAxis(AxisKind kind, float rad);
};

// EOF