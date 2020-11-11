/**
 * @file MyMath.cpp
 * @brief 計算管理クラス
 */
#include "MyMath.h"
#include "Transform.h"

 /**
  * @brief   クォータニオン作成
  * @param   axis    回転させる軸
  * @param   radian  回転させる角度(ラジアン)
  * @return  作成したクォータニオン
  */
Quaternion MakeQuaternion(Vector3 axis, float radian);

 /**
  * @brief   クォータニオンの掛け算
  * @param   left    計算の左の項
  * @param   right   計算の右の項
  * @return  計算したクォータニオン
  */
Quaternion CalcQuaternion(Quaternion left, Quaternion right);

DirectX::XMFLOAT4X4 MyMath::StoreXMFloat4x4(const Transform& transform)
{
	DirectX::XMFLOAT4X4 mtx = XMFLOAT4X4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);

	if (&transform == nullptr) {// 参照渡しだから何とか出来るはず
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

/**
 * @brief クォータニオンを角度で回転
 * @return 回転後のクオータニオン
 */
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
 * @brief   クォータニオン作成
 * @param   axis    回転させる軸
 * @param   radian  回転させる角度(ラジアン)
 * @return  作成したクォータニオン
 */
Quaternion MakeQuaternion(Vector3 axis, float radian)
{
	Quaternion quaternion;      //!< 作成するクォータニオン
	float halfSin, halfCos;      //!< 動かす角度の半分のsin,cos
	float normal;

	quaternion = { 1,0,0,0 };
	// 回転軸の長さを求める
	normal = axis.x * axis.x + axis.y * axis.y + axis.z * axis.z;
	if (normal <= 0.0f) return quaternion;

	// 方向ベクトルへ（単位ベクトル：長さは1）
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
 * @brief   クォータニオンの掛け算
 * @param   left    計算の左の項
 * @param   right   計算の右の項
 * @return  計算したクォータニオン
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
 * @brief   クォータニオンによる回転
 * @param   axis    回転させたい軸
 * @param   pos     回転させるオブジェクトの座標
 * @param   radius  回転させる角度
 * @return  回転後の座標
 */
Vector3 MyMath::RotateQuaternionPosition(Vector3 axis, Vector3 pos, float radian)
{
	Quaternion  complexNumber, complexConjugateNumber;
	Quaternion  posQuaternion = { 0, pos.x, pos.y, pos.z };
	Vector3     resultPosition;

	if (axis.x == 0 && axis.y == 0 && axis.z == 0 ||
		radian == 0) {
		return pos;
	}

	complexNumber = MakeQuaternion(axis, radian);
	complexConjugateNumber = MakeQuaternion(axis, -radian);

	posQuaternion = CalcQuaternion(complexNumber, posQuaternion);
	posQuaternion = CalcQuaternion(posQuaternion, complexConjugateNumber);

	resultPosition.x = posQuaternion.x;
	resultPosition.y = posQuaternion.y;
	resultPosition.z = posQuaternion.z;

	return resultPosition;
}

/**
 * @brief ベクトルをクォータニオンで回転
 * @return 回転後のベクトル
 */
Vector3 MyMath::Vector3xQuaternion(Vector3 vec, Quaternion quat)
{
	Quaternion vecQuat = { 0, vec.x, vec.y ,vec.z };
	vecQuat = CalcQuaternion(vecQuat, quat);

	return { vecQuat.x, vecQuat.y, vecQuat.z };
}

/**
 * @brief 座標をクォーテーションで回転
 * @return 回転後の座標
 */
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

/**
 * @brief 度数をラジアンに変換
 * @return ラジアン
 */
float MyMath::AngleToRadian(float angle)
{
	float radian = 0.f;

	radian = angle / 180 * 3.14f;

	return radian;
}

/**
 * @brief 対象方向へ向くクォータニオンを求める
 * @return 対象方向への回転クォータニオン
 */
Quaternion MyMath::LookAt(Vector3 myPos, Vector3 targetPos)
{
	Quaternion result;
	Vector3 target = targetPos - myPos;
	Vector3 forward = Vector3(0, 0, 1);
	Vector3 axis = Vector3(1, 0, 0);
	float dot = 0;
	float radian = 0;

	Normalize(target);
	dot = Dot(forward, target);
	radian = acosf(dot);
	axis = Cross(forward, target);

	result = MakeQuaternion(axis, radian);

	return result;
}

/**
 * @brief 内積を求める
 */
float MyMath::Dot(Vector3 vec1, Vector3 vec2)
{
	float result = 0;

	result = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;

	return result;
}

/**
 * @brief 外積を求める
 */
Vector3 MyMath::Cross(Vector3 myPos, Vector3 targetPos)
{
	Vector3 cross = Vector3();

	cross.x = myPos.y * targetPos.z - myPos.z * targetPos.y;
	cross.y = myPos.z * targetPos.x - myPos.x * targetPos.z;
	cross.z = myPos.x * targetPos.y - myPos.y * targetPos.x;

	return cross;
}

/**
 * @brief 単位ベクトルへ変換
 * @return なし
 */
void MyMath::Normalize(Vector3 &vec)
{
	float scalar = 1;

	scalar = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

	vec /= scalar;
}

// EOF