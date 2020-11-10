/**
 * @file MyMath.h
 * @brief 計算管理クラス
 */
#pragma once
#include <DirectXMath.h>

 /**
  * @brief クォータニオン
  */
struct Quaternion
{
	float w;
	float x;
	float y;
	float z;
};

/**
 * @brief 3次元用
 */
struct Vector3
{
	float x, y, z;
	Vector3() = default;
	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3 operator+ (const Vector3 num) {
		Vector3 value;
		value.x = x + num.x;
		value.y = y + num.y;
		value.z = z + num.z;
		return value;
	}
	Vector3 operator- (const Vector3 num) {
		Vector3 value;
		value.x = x - num.x;
		value.y = y - num.y;
		value.z = z - num.z;
		return value;
	}
	Vector3 operator* (const Vector3 num) {
		Vector3 value;
		value.x = x * num.x;
		value.y = y * num.y;
		value.z = z * num.z;
		return value;
	}
	Vector3 operator/ (const Vector3 num) {
		Vector3 value;
		value.x = x / num.x;
		value.y = y / num.y;
		value.z = z / num.z;
		return value;
	}
	Vector3& operator= (const Vector3 num) {
		x = num.x;
		y = num.y;
		z = num.z;
		return *this;
	}
	Vector3& operator+= (const Vector3 num) {
		x = x + num.x;
		y = y + num.y;
		z = z + num.z;
		return *this;
	}
	Vector3& operator-= (const Vector3 num) {
		x = x - num.x;
		y = y - num.y;
		z = z - num.z;
		return *this;
	}
	Vector3& operator*= (const Vector3 num) {
		x = x * num.x;
		y = y * num.y;
		z = z * num.z;
		return *this;
	}
	Vector3& operator/= (const Vector3 num) {
		x = x / num.x;
		y = y / num.y;
		z = z / num.z;
		return *this;
	}

	Vector3 operator+ (const float num) {
		Vector3 value;
		value.x = x + num;
		value.y = y + num;
		value.z = z + num;
		return value;
	}
	Vector3 operator- (const float num) {
		Vector3 value;
		value.x = x - num;
		value.y = y - num;
		value.z = z - num;
		return value;
	}
	Vector3 operator* (const float num) {
		Vector3 value;
		value.x = x * num;
		value.y = y * num;
		value.z = z * num;
		return value;
	}
	Vector3 operator/ (const float num) {
		Vector3 value;
		value.x = x / num;
		value.y = y / num;
		value.z = z / num;
		return value;
	}
	Vector3 operator+= (const float num) {
		x = x + num;
		y = y + num;
		z = z + num;
		return *this;
	}
	Vector3 operator-= (const float num) {
		x = x - num;
		y = y - num;
		z = z - num;
		return *this;
	}
	Vector3 operator*= (const float num) {
		x = x * num;
		y = y * num;
		z = z * num;
		return *this;
	}
	Vector3 operator/= (const float num) {
		x = x / num;
		y = y / num;
		z = z / num;
		return *this;
	}
	Vector3& operator= (const float num) {
		x = num;
		y = num;
		z = num;
		return *this;
	}
};

class Transform;

/**
 * @brief 自作の計算クラス
 */
class MyMath
{
public:
	static DirectX::XMFLOAT4X4 StoreXMFloat4x4(const Transform& transform);

	static Quaternion AnglexQuaternion(Quaternion quat, Vector3 axis, float radius);

	/**
	 * @brief   クォータニオンによる回転
	 * @param   axis    回転させたい軸
	 * @param   pos     回転させるオブジェクトの座標
	 * @param   radius  回転させる角度
	 * @return  回転後の座標
	 */
	static Vector3 RotateQuaternionPosition(Vector3 axis, Vector3 pos, float radius);

	static Vector3 Vector3xQuaternion(Vector3 vec, Quaternion quat);

	static Vector3 PosxQuaternion(Vector3 pos , Quaternion quat);

	static float AngleToRadian(float angle);
	
	/**
	 * @brief 対象方向へ向くクォータニオンを求める
	 * @return 対象方向への回転クォータニオン
	 */
	static Quaternion LookAt(Vector3 myPos, Vector3 targetPos);

	/**
	 * @brief 内積を求める
	 */
	static float Dot(Vector3 vec1, Vector3 vec2);

	/**
	 * @brief 外積を求める
	 */
	static Vector3 Cross(Vector3 myPos, Vector3 targetPos);

	/**
	 * @brief 単位ベクトルへ変換
	 * @return なし
	 */
	static void Normalize(Vector3 &vec);
};

// EOF