/**
 * @file MissileCtrl
 * @brief ’e‚Ì§ŒäƒRƒ“ƒ|[ƒlƒ“ƒg
 */
#pragma once
#include "Component.h"
#include "MyMath.h"

class GameObject;

/**
 * @class MissileCtrl
 * @brief ’e‚Ì§Œä
 */
class MissileCtrl :public Component
{
protected:
	int m_nLife;			//!< õ–½
	int m_power;		//!< ’e‚ÌˆĞ—Í
	GameObject* m_target;
	Transform* m_parentTrans;

public:
	/**
	 * @brief ‰Šú‰»ˆ—
	 * @return ‚È‚µ
	 */
	virtual void Awake();

	HRESULT Init();

	void Update();

	/**
	 * ’e‚ÌˆĞ—Í‚Ìæ“¾
	 * @return ’e‚ÌˆĞ—Í
	 */
	virtual int GetPower();


	bool Fire(Vector3* pos);

	bool Fire(Vector3* pos, Quaternion quat);
	bool Fire(Vector3* pos, Quaternion quat, GameObject* target);
};

// EOF