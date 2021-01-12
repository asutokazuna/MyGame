/**
 * @file MissileCtrl
 * @brief 弾の制御コンポーネント
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
	GameObject* m_target;
	Transform* m_parentTrans;

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	virtual void Awake();

	HRESULT Init();

	void Update();

	/**
	 * 弾の威力の取得
	 * @return 弾の威力
	 */
	virtual int GetPower();


	bool Fire(Vector3* pos);

	bool Fire(Vector3* pos, Quaternion quat);
	bool Fire(Vector3* pos, Quaternion quat, GameObject* target);
};

// EOF