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
 * @brief トランスフォームをDirectXの4x4行列へ変換
 * @param[in] transform 変換したいトランスフォーム
 * @return 変換した4x4行列
 */
DirectX::XMFLOAT4X4 MyMath::StoreXMFloat4x4(const Transform& transform)
{
	DirectX::XMFLOAT4X4 mtx = XMFLOAT4X4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);

	if (&transform == nullptr) {// 参照渡しだから本来は何とか出来るはず
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

	// ローカル
	mtxScale = XMMatrixScaling(transform.localScale.x, transform.localScale.y, transform.localScale.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScale);

	mtxRot = XMMatrixRotationRollPitchYaw(transform.localRotation.x, transform.localRotation.y, transform.localRotation.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);
	mtxAxis = mtxRot;

	mtxTranslate = XMMatrixTranslation(transform.localPosition.x, transform.localPosition.y, transform.localPosition.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	quat = XMLoadFloat4(&f4);

	mtxQuat = XMMatrixRotationQuaternion(quat);

	// ワールド
	mtxScale = XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScale);
	mtxRot = XMMatrixRotationRollPitchYaw(transform.rotation.x, transform.rotation.y, transform.rotation.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);
	mtxRot = XMMatrixMultiply(mtxRot, mtxQuat);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);


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
Quaternion MyMath::CalcQuaternion(const Quaternion& left, const Quaternion& right)
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
Vector3 MyMath::RotateQuaternionPosition(const Vector3& axis, const Vector3& pos,const float& radian)
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
Vector3 MyMath::Vector3xQuaternion(const Vector3& vec, const Quaternion& quat)
{
	Quaternion vecQuat = { 0, vec.x, vec.y ,vec.z };
	vecQuat = CalcQuaternion(vecQuat, quat);

	return { vecQuat.x, vecQuat.y, vecQuat.z };
}

/**
 * @brief 座標をクォーテーションで回転
 * @return 回転後の座標
 */
Vector3 MyMath::PosxQuaternion(const Vector3& pos, Quaternion quat)
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
float MyMath::AngleToRadian(const float& angle)
{
	float radian = 0.f;

	radian = angle / 180 * 3.14f;

	return radian;
}

/**
 * @brief 行列をクォータニオンに変換
 * @param[in] matrix 変換したい行列
 * @return 変換したクォータニオン
 */
Quaternion MyMath::MatrixToQuaternion(float4x4 & matrix)
{
	Quaternion result = Quaternion();
	float elem[4];
	elem[0] =  matrix._11 - matrix._22 - matrix._33 + 1.0f;
	elem[1] = -matrix._11 + matrix._22 - matrix._33 + 1.0f;
	elem[2] = -matrix._11 - matrix._22 + matrix._33 + 1.0f;
	elem[3] =  matrix._11 + matrix._22 + matrix._33 + 1.0f;

	int biggestIdx = 0;
	for (int i = 0; i < 4; i++)
	{
		if (elem[i] > elem[biggestIdx])
		{
			biggestIdx = i;
		}
	}

	if (elem[biggestIdx] < 0)
	{
		return result;
	}

	float q[4];
	float v = sqrtf(elem[biggestIdx]) * 0.5f;
	q[biggestIdx] = v;
	float mult = 0.25f / v;

	switch (biggestIdx)
	{
	case 0: // x
		q[1] = (matrix._12 + matrix._21) * mult;
		q[2] = (matrix._31 + matrix._13) * mult;
		q[3] = (matrix._32 - matrix._23 ) * mult;
		break;
	case 1: // y
		q[0] = (matrix._12 + matrix._21) * mult;
		q[2] = (matrix._23 + matrix._32) * mult;
		q[3] = (matrix._13 - matrix._31) * mult;
		break;
	case 2: // z
		q[0] = (matrix._31 + matrix._13) * mult;
		q[1] = (matrix._23 + matrix._32) * mult;
		q[3] = (matrix._21 - matrix._12) * mult;
		break;
	case 3: // w
		q[0] = (matrix._32 - matrix._23) * mult;
		q[1] = (matrix._13 - matrix._31) * mult;
		q[2] = (matrix._21 - matrix._12) * mult;
		break;
	}

	result.x = q[0];
	result.y = q[1];
	result.z = q[2];
	result.w = q[3];

	return result;
}

/**
 * @brief 対象方向へ向くクォータニオンを求める
 * @return 対象方向への回転クォータニオン
 */
Quaternion MyMath::LookAt(const Vector3& myPos, const Vector3& targetPos, Vector3 axis)
{
	Quaternion result;
//	Quaternion temp;
	Vector3 target = targetPos - myPos;
	Vector3 forward = Vector3(0, 0, 1);
	Vector3 up = Vector3(0, 1, 0);
	Vector3 right = Vector3(1, 0, 0);
	Vector3 newUp;
	//Vector3 newRight;
//	Vector3 newForward;
//	Vector3 temptarget;
	float dot = 0;
	float radian = 0;

	Normalize(target);
	dot = Dot(forward, target);
	radian = acosf(dot);

	newUp = Cross(forward, target);
	result = MakeQuaternion(newUp, radian);

	return result;
}

/**
 * @brief 対象方向へ向くクォータニオンを求める
 * @param[in] 向かせたい方向ベクトル
 * @return 対象方向への回転クォータニオン
 * @details 上方向を(0,1,0)で固定しているので捻じれずに対象方向へ向くことができる
 */
Quaternion MyMath::LookAt(const Vector3 & dir)
{
	Vector3 z = dir;
	MyMath::Normalize(z);
	Vector3 x = Cross(Vector3(0,1,0), z);
	MyMath::Normalize(x);
	Vector3 y = Cross(z, x);
	MyMath::Normalize(y);

	float4x4 m = float4x4::Identity();
	m._11 = x.x; m._12 = y.x; m._13 = z.x;
	m._21 = x.y; m._22 = y.y; m._23 = z.y;
	m._31 = x.z; m._32 = y.z; m._33 = z.z;

	Quaternion rot = MatrixToQuaternion(m);

	return rot;
}

/**
 * @brief 内積を求める
 */
float MyMath::Dot(const Vector3& vec1,const Vector3& vec2)
{
	float result = 0;

	result = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;

	return result;
}

/**
 * @brief 外積を求める
 */
Vector3 MyMath::Cross(const Vector3& myPos,const Vector3& targetPos)
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

	if (scalar == 0) {
		vec = Vector3(0, 0, 1);
		return;
	}

	vec /= scalar;
}

/**
 * @brief 線形補間
 */
float MyMath::Lerp(const float& start,const float& end,const float& t)
{
	return start + (end - start) * t;
}

/**
 * @brief 絶対値を求める
 * @param[in] value 変換したい値
 * @return 入力値の絶対値
 */
Vector3 MyMath::Abs(const Vector3& value)
{
	Vector3	result = value;

	result.x = fabsf(result.x);
	result.y = fabsf(result.y);
	result.z = fabsf(result.z);

	return result;
}

/**
 * @brief 距離を求める
 * @param[in] pos 自分の座標
 * @param[in] othorPos 相手の座標
 * @return 長さ
 */
float MyMath::Distance(const Vector3& pos, const Vector3& othorPos)
{
	Vector3 vec = othorPos - pos;
	float result = 0;

	result = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

	return result;
}

/**
 * @brief 変換
 */
DirectX::XMFLOAT4X4 MyMath::LoadPosisiton(Vector3 pos)
{
	XMFLOAT4X4 mtx = XMFLOAT4X4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1);

	mtx._41 = pos.x;
	mtx._42 = pos.y;
	mtx._43 = pos.z;
	return mtx;
}

// EOF