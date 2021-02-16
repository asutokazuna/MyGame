/**
 * @file Transform.h
 * @brief 座標管理クラス
 * @author Ariga
 */
#pragma once
#include "Component.h"
#include "MyMath.h"
#include "Tween.h"

// 前方宣言
class Tween;

/**
 * @class Transform
 * @brief 座標管理クラス
 */
class Transform : public Component
{
public:
	Vector3 position;		//!< 座標
	Vector3 rotation;		//!< 角度
	Vector3 scale;			//!< 大きさ
	Vector3 localPosition;	//!< ローカル座標
	Vector3 localRotation;	//!< ローカル角度
	Vector3 localScale;		//!< ローカルサイズ
	Vector3 axisX;			//!< ローカルX軸方向
	Vector3 axisY;			//!< ローカルY軸方向
	Vector3 axisZ;			//!< ローカルZ軸方向
	Quaternion quaternion;	//!< クォータニオン
	Quaternion localQuaternion;

public:
	Tween* Do;

	/**
	 * =演算子のオーバーロード
	 */
	Transform& operator= (const Transform trs) {
		position = trs.position;
		rotation = trs.rotation;
		scale = trs.scale;
		localPosition = trs.localPosition;
		localRotation = trs.localRotation;
		localScale = trs.localScale;
		axisX = trs.axisX;
		axisY = trs.axisY;
		axisZ = trs.axisZ;
		quaternion = trs.quaternion;
		localQuaternion = trs.localQuaternion;
		*(Do) = *(trs.Do);
		//Tween t;
		//t = *trs.Do;
		return *this;
	}

	/**
	 * @brief コンストラクタ
	 */
	Transform();

	/**
	* @brief コピーコンストラクタ
	*/
	Transform(const Transform &trans);

	/**
	 * @brrief デストラクタ
	 */
	~Transform();

	//void Draw();

	/**
	 * @brief 座標の取得
	 * @return 座標
	 */
	Vector3 GetPosition();

	/**
	 * @brief 回転の取得
	 * @return 回転
	 */
	Vector3 GetRotation();

	/**
	 * @brief 大きさの取得
	 * @return 大きさ
	 */
	Vector3 GetScale();

	/**
	 * @brief 前方向の取得
	 * @return 前方向
	 */
	Vector3 GetForward();

	/**
	 * @brief 右方向の取得
	 * @return 右方向
	 */
	Vector3 GetRight();

	/**
	 * @brief 上方向の取得
	 * @return 上方向
	 */
	Vector3 GetUp();

	/**
	 * @brief 軸方向
	 */
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
	 * @brief 回転させる
	 * @param[in]	kind 回転させる軸
	 * @param[in]	rad	回転させる角度(ラジアン)
	 * @return 実体
	 */
	Transform& AngleAxis(AxisKind kind, float rad);
};

// EOF