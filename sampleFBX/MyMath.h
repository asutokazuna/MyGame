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
	Quaternion() = default;
	Quaternion(float w, float x, float y, float z)
	{
		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

struct float4x4
{
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
	float4x4() = default;
	float4x4(float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44) 
{
		this->_11 = _11;
		this->_12 = _12;
		this->_13 = _13;
		this->_14 = _14;
		this->_21 = _21;
		this->_22 = _22;
		this->_23 = _23;
		this->_24 = _24;
		this->_31 = _31;
		this->_32 = _32;
		this->_33 = _33;
		this->_34 = _34;
		this->_44 = _41;
		this->_44 = _42;
		this->_44 = _43;
		this->_44 = _44;
	}

	static float4x4 Identity()
	{
		return float4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
	}
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
	Vector3(float num) {
		this->x = num;
		this->y = num;
		this->z = num;
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
	const bool operator == (const Vector3& val)
	{
		if (x == val.x && y == val.y && z == val.z)
		{
			return true;
		}
		return false;
	}
	const bool operator != (const Vector3& val)
	{
		if (x == val.x || y == val.y || z == val.z)
		{
			return false;
		}
		return true;
	}
};

class Transform;

/**
 * @brief 自作の計算クラス
 */
class MyMath
{
public:
	/**
	 * @brief トランスフォームをDirectXの4x4行列へ変換
	 * @param[in] transform 変換したいトランスフォーム
	 * @return 変換した4x4行列
	 */
	static DirectX::XMFLOAT4X4 StoreXMFloat4x4(const Transform& transform);

	/**
	* @brief   クォータニオンの掛け算
	* @param   left    計算の左の項
	* @param   right   計算の右の項
	* @return  計算したクォータニオン
	*/
	static Quaternion CalcQuaternion(const Quaternion& left, const Quaternion& right);

	/**
	 * @brief クォータニオンを角度で回転
	 * @return 回転後のクオータニオン
	 */
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
	 * @brief 行列をクォータニオンに変換
	 * @param[in] matrix 変換したい行列
	 * @return 変換したクォータニオン
	 */
	static Quaternion MatrixToQuaternion(float4x4& matrix);
	
	/**
	 * @brief 対象方向へ向くクォータニオンを求める
	 * @return 対象方向への回転クォータニオン
	 */
	static Quaternion LookAt(const Vector3& myPos, const Vector3& targetPos, Vector3 axis = Vector3(0, 1, 0));

	/**
	 * @brief 対象方向へ向くクォータニオンを求める
	 * @param[in] 向かせたい方向ベクトル
	 * @return 対象方向への回転クォータニオン
	 * @details 上方向を(0,1,0)で固定しているので捻じれずに対象方向へ向くことができる
	 */
	static Quaternion LookAt(const Vector3& dir);

	static Quaternion LookRotation(Vector3 forward, Vector3 dir, float maxRadian);

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

	/**
	 * @brief 線形補間
	 */
	static float Lerp(const float& start, const float& end, const float & t);

	/**
	 * @brief 線形補間
	 */
	static Vector3 Lerp(const Vector3& start, const Vector3& end, const float & t);

	/**
	 * @brief 絶対値を求める
	 * @param[in] value 変換したい値
	 * @return 入力値の絶対値
	 */
	static Vector3 Abs(const Vector3 & value);

	/**
	 * @brief 距離を求める
	 * @param[in] pos 自分の座標
	 * @param[in] othorPos 相手の座標
	 * @return 長さ
	 */
	static float Distance(const Vector3& pos, const Vector3& othorPos);

	static DirectX::XMFLOAT4X4 LoadPosisiton(Vector3 pos);

	/**
	 * @brief 球面線形補間
	 * @param[in] start 始点
	 * @param[in] end 終点
	 * @param[in] t 割合
	 * @return 補間した数値
	 */
	static Vector3 Slerp(const Vector3& start, const Vector3 end, const float t);

	template<typename Ty>
	static const Ty _0 = static_cast<Ty>(0);
	template<typename Ty>
	static const Ty _1 = static_cast<Ty>(1);
	template<typename Ty>
	static constexpr Ty _1_5 = static_cast<Ty>(1.5f);
	template<typename Ty>
	static constexpr Ty _1_525 = static_cast<Ty>(1.525f);

	template<typename Ty>
	static constexpr Ty _2 = static_cast<Ty>(2);
	template<typename Ty = float>
	static inline Ty InQuint(float time, Ty max = _1<Ty>, Ty min = _0<Ty>, float totaltime = 1)
	{
		max -= min;
		time /= totaltime;

		return max * time * time * time * time * time + min;
	}

	template<typename Ty = float>
	static inline Ty OutQuint(float time, Ty max = _1<Ty>, Ty min = _0<Ty>, float totaltime = 1)
	{
		max -= min;
		time = time / totaltime - _1<Ty>;

		return max * (time * time * time * time * time + _1<Ty>) + min;
	}

	template<typename Ty = float>
	static inline Ty InOutQuint(float time, Ty max = _1<Ty>, Ty min = _0<Ty>, float totaltime = 1)
	{
		max -= min;
		time /= totaltime;

		if (time / _2<Ty> < _1<Ty>)
			return max / _2<Ty> * time * time * time * time * time + min;

		time -= _2<Ty>;

		return max / _2<Ty> * (time * time * time * time * time + _2<Ty>) + min;
	}

	static inline Vector3 InQuint(float time, Vector3 max, Vector3 min , float totaltime = 1)
	{
		max -= min;
		time /= totaltime;

		return max * time * time * time * time * time + min;
	}

	static Vector3 OutQuint(float time, Vector3 max, Vector3 min, float totaltime = 1)
	{
		max -= min;
		time = time / totaltime - 1;

		return max * (time * time * time * time * time + 1) + min;
	}
	static Vector3 InOutQuint(float time, Vector3 max, Vector3 min, float totaltime = 1);


	//static inline Vector3 OutInQuint(float time, Vector3 max, Vector3 min, float totaltime = 1)
	//{
	//	max -= min;
	//	time /= totaltime;

	//	if (time / 2 < 0.5f) {
	//		time -= 2;
	//		return max / 2 * (time * time * time * time * time + 2) + min;

	//	}

	//	return max / 2 * time * time * time * time * time + min;
	//}

};

// EOF