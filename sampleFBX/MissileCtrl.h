/**
 * @file MissileCtrl
 * @brief 弾の制御コンポーネント
 * @author Ariga
 */
#pragma once
#include "Component.h"
#include "MyMath.h"

class GameObject;

/**
 * @class MissileCtrl
 * @brief 弾の制御
 */
class MissileCtrl :public Component
{
protected:
	int m_nLife;			//!< 寿命
	int m_power;		//!< 弾の威力
	GameObject* m_target;	//!< 追従オブジェクト

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	virtual void Awake();

	HRESULT Init();

	/**
	 * @brief 更新処理
	 * @return なし
	 */
	void Update();

	/**
	 * 弾の威力の取得
	 * @return 弾の威力
	 */
	virtual int GetPower();


	/**
	 * @brief 弾の発射処理
	 * @param[in] pos 発射座標
	 * @return なし
	 */
	void Fire(Vector3* pos);

	/**
	 * @brief 弾の発射処理
	 * @param[in] pos 発射座標
	 * @param[in] quat 発射方向
	 * @return なし
	 */
	void Fire(Vector3* pos, Quaternion quat);

	/**
	 * @brief 弾の発射処理
	 * @param[in] pos 発射座標
	 * @param[in] quat 発射方向
	 * @param[in] target 追従オブジェクト
	 * @return なし
	 */
	void Fire(Vector3* pos, Quaternion quat, GameObject* target);
};

// EOF