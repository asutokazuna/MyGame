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
	
	Vector3 operator+ (const Vector3 num) const{
		Vector3 value;
		value.x = x + num.x;
		value.y = y + num.y;
		value.z = z + num.z;
		return value;
	}
	Vector3 operator- (const Vector3 num) const{
		Vector3 value;
		value.x = x - num.x;
		value.y = y - num.y;
		value.z = z - num.z;
		return value;
	}
	Vector3 operator* (const Vector3 num) const{
		Vector3 value;
		value.x = x * num.x;
		value.y = y * num.y;
		value.z = z * num.z;
		return value;
	}
	Vector3 operator/ (const Vector3 num) const{
		Vector3 value;
		value.x = x / num.x;
		value.y = y / num.y;
		value.z = z / num.z;
		return value;
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

	/**
	* @brief   クォータニオンの掛け算
	* @param   left    計算の左の項
	* @param   right   計算の右の項
	* @return  計算したクォータニオン
	*/
	static Quaternion CalcQuaternion(const Quaternion& left, const Quaternion& right);

	static Quaternion AnglexQuaternion(Quaternion quat, Vector3 axis, float radius);

	/**
	 * @brief   クォータニオンによる回転
	 * @param   axis    回転させたい軸
	 * @param   pos     回転させるオブジェクトの座標
	 * @param   radius  回転させる角度
	 * @return  回転後の座標
	 */
	static Vector3 RotateQuaternionPosition(const Vector3& axis, const Vector3& pos, const float& radian);
	
	/**
	 * @brief ベクトルをクォータニオンで回転
	 * @return 回転後のベクトル
	 */
	static Vector3 Vector3xQuaternion(const Vector3& vec, const Quaternion& quat);

	/**
	 * @brief 座標をクォーテーションで回転
	 * @return 回転後の座標
	 */
	static Vector3 PosxQuaternion(const Vector3& pos, Quaternion quat);

	/**
	 * @brief 度数をラジアンに変換
	 * @return ラジアン
	 */
	static float AngleToRadian(const float& angle);
	
	/**
	 * @brief 対象方向へ向くクォータニオンを求める
	 * @return 対象方向への回転クォータニオン
	 */
	static Quaternion LookAt(const Vector3& myPos, const Vector3& targetPos);

	/**
	 * @brief 内積を求める
	 */
	static float Dot(const Vector3& vec1, const Vector3& vec2);

	/**
	 * @brief 外積を求める
	 */
	static Vector3 Cross(const Vector3& myPos, const Vector3& targetPos);

	/**
	 * @brief 単位ベクトルへ変換
	 * @return なし
	 */
	static void Normalize(Vector3 &vec);
	//static Vector3 Lerp(const Vector3 start, const Vector3 end, const float & t);
	static float Lerp(const float& start, const float& end, const float & t);
	static Vector3 Abs(const Vector3 & value);
	static DirectX::XMFLOAT4X4 LoadPosisiton(Vector3 pos);
};

// EOF