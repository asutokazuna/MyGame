/**
 * @file MyMath.cpp
 * @brief �v�Z�Ǘ��N���X
 */
#include "MyMath.h"
#include "Transform.h"

 /**
  * @brief   �N�H�[�^�j�I���쐬
  * @param   axis    ��]�����鎲
  * @param   radian  ��]������p�x(���W�A��)
  * @return  �쐬�����N�H�[�^�j�I��
  */
Quaternion MakeQuaternion(Vector3 axis, float radian);

 /**
  * @brief   �N�H�[�^�j�I���̊|���Z
  * @param   left    �v�Z�̍��̍�
  * @param   right   �v�Z�̉E�̍�
  * @return  �v�Z�����N�H�[�^�j�I��
  */
Quaternion CalcQuaternion(Quaternion left, Quaternion right);

DirectX::XMFLOAT4X4 MyMath::StoreXMFloat4x4(const Transform& transform)
{
	DirectX::XMFLOAT4X4 mtx = XMFLOAT4X4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);

	if (&transform == nullptr) {// �Q�Ɠn�������牽�Ƃ��o����͂�
		return mtx;
	}

	DirectX::XMMATRIX mtxWorld, mtxScale, mtxRot, mtxTranslate,mtxAxis,mtxQuat;
	XMVECTOR quat;
	XMFLOAT4 f4;
	f4.w = transform.quaternion.w;
	f4.x = transform.quaternion.x;
	f4.y = transform.quaternion.y;
	f4.z = transform.quaternion.z;

	mtxRot = mtxWorld = XMMatrixIdentity();

	mtxScale = XMMatrixScaling(transform.localScale.x, transform.localScale.y, transform.localScale.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScale);

	mtxRot = XMMatrixRotationRollPitchYaw(transform.localRotation.x, transform.localRotation.y, transform.localRotation.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);
	mtxAxis = mtxRot;

	quat = XMLoadFloat4(&f4);

	mtxQuat = XMMatrixRotationQuaternion(quat);

	mtxScale = XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z);
	//mtxScale = XMMatrixMultiply(mtxScale, mtxQuat);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScale);

	//mtxRot = XMMatrixRotationRollPitchYaw(transform.rotation.x, transform.rotation.y, transform.rotation.z);
	mtxRot = XMMatrixMultiply(mtxRot, mtxQuat);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	mtxTranslate = XMMatrixTranslation(transform.localPosition.x, transform.localPosition.y, transform.localPosition.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	//Vector3 pos= 
	//MyMath::Vector3xQuaternion(transform.position, transform.quaternion);
	mtxTranslate = XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z);
	//mtxTranslate = XMMatrixMultiply(mtxTranslate, mtxQuat);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	//XMMatrixRotationQuaternion();

	XMStoreFloat4x4(&mtx, mtxWorld);

	return mtx;
}

Quaternion MyMath::AnglexQuaternion(Quaternion quat, Vector3 axis, float radian)
{
	Quaternion result;
	Quaternion complexNumber;

	if (radian == 0) {
		return quat;
	}

	complexNumber = MakeQuaternion(axis, radian);

	result = CalcQuaternion(complexNumber, quat);

	return result;
}

/**
 * @brief   �N�H�[�^�j�I���쐬
 * @param   axis    ��]�����鎲
 * @param   radian  ��]������p�x(���W�A��)
 * @return  �쐬�����N�H�[�^�j�I��
 */
Quaternion MakeQuaternion(Vector3 axis, float radian)
{
	Quaternion quaternion;      //!< �쐬����N�H�[�^�j�I��
	float halfSin, halfCos;      //!< �������p�x�̔�����sin,cos
	float normal;

	quaternion = { 0,0,0,0 };
	// ��]���̒��������߂�
	normal = axis.x * axis.x + axis.y * axis.y + axis.z * axis.z;
	if (normal <= 0.0f) return quaternion;

	// �����x�N�g���ցi�P�ʃx�N�g���F������1�j
	normal = 1.0f / sqrtf(normal);
	axis = axis * normal;


	halfSin = sinf(radian * 0.5f);
	halfCos = cosf(radian * 0.5f);

	quaternion.w = halfCos;
	quaternion.x = axis.x * halfSin;
	quaternion.y = axis.y * halfSin;
	quaternion.z = axis.z * halfSin;

	return quaternion;
}

/**
 * @brief   �N�H�[�^�j�I���̊|���Z
 * @param   left    �v�Z�̍��̍�
 * @param   right   �v�Z�̉E�̍�
 * @return  �v�Z�����N�H�[�^�j�I��
 */
Quaternion CalcQuaternion(Quaternion left, Quaternion right)
{
	Quaternion quaternion;
	float   num1, num2, num3, num4;

	num1 = left.w * right.w;
	num2 = -left.x * right.x;
	num3 = -left.y * right.y;
	num4 = -left.z * right.z;
	quaternion.w = num1 + num2 + num3 + num4;

	num1 = left.w * right.x;
	num2 = left.x * right.w;
	num3 = left.y * right.z;
	num4 = -left.z * right.y;
	quaternion.x = num1 + num2 + num3 + num4;

	num1 = left.w * right.y;
	num2 = left.y * right.w;
	num3 = left.z * right.x;
	num4 = -left.x * right.z;
	quaternion.y = num1 + num2 + num3 + num4;

	num1 = left.w * right.z;
	num2 = left.z * right.w;
	num3 = left.x * right.y;
	num4 = -left.y * right.x;
	quaternion.z = num1 + num2 + num3 + num4;

	return   quaternion;
}

/**
 * @brief   �N�H�[�^�j�I���ɂ���]
 * @param   axis    ��]����������
 * @param   pos     ��]������I�u�W�F�N�g�̍��W
 * @param   radius  ��]������p�x
 * @return  ��]��̍��W
 */
Vector3 MyMath::RotateQuaternionPosition(Vector3 axis, Vector3 pos, float radius)
{
	Quaternion  complexNumber, complexConjugateNumber;
	Quaternion  posQuaternion = { 0, pos.x, pos.y, pos.z };
	Vector3     resultPosition;

	if (axis.x == 0 && axis.y == 0 && axis.z == 0 ||
		radius == 0) {
		return pos;
	}

	complexNumber = MakeQuaternion(axis, radius);
	complexConjugateNumber = MakeQuaternion(axis, -radius);

	posQuaternion = CalcQuaternion(complexNumber, posQuaternion);
	posQuaternion = CalcQuaternion(posQuaternion, complexConjugateNumber);

	resultPosition.x = posQuaternion.x;
	resultPosition.y = posQuaternion.y;
	resultPosition.z = posQuaternion.z;

	return resultPosition;
}

Vector3 MyMath::Vector3xQuaternion(Vector3 vec, Quaternion quat)
{
	Quaternion vecQuat = { 0, vec.x, vec.y ,vec.z };
	vecQuat = CalcQuaternion(vecQuat, quat);

	return { vecQuat.x, vecQuat.y, vecQuat.z };
}

Vector3 MyMath::PosxQuaternion(Vector3 pos, Quaternion quat)
{
	Quaternion vecQuat = { 0, pos.x, pos.y ,pos.z };
	vecQuat = CalcQuaternion(quat, vecQuat);
	quat.x = -quat.x;
	quat.y = -quat.y;
	quat.z = -quat.z;
	vecQuat = CalcQuaternion(vecQuat, quat);

	return { vecQuat.x, vecQuat.y, vecQuat.z };
}

float MyMath::AngleToRadian(float angle)
{
	float radian = 0.f;

	radian = angle / 180 * 3.14f;

	return radian;
}

// EOF