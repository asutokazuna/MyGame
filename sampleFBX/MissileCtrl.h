/**
 * @file MissileCtrl
 * @brief �e�̐���R���|�[�l���g
 */
#pragma once
#include "Component.h"
#include "MyMath.h"

class GameObject;

/**
 * @class MissileCtrl
 * @brief �e�̐���
 */
class MissileCtrl :public Component
{
protected:
	int m_nLife;			//!< ����
	int m_power;		//!< �e�̈З�
	GameObject* m_target;
	Transform* m_parentTrans;

public:
	/**
	 * @brief ����������
	 * @return �Ȃ�
	 */
	virtual void Awake();

	HRESULT Init();

	void Update();

	/**
	 * �e�̈З͂̎擾
	 * @return �e�̈З�
	 */
	virtual int GetPower();


	bool Fire(Vector3* pos);

	bool Fire(Vector3* pos, Quaternion quat);
	bool Fire(Vector3* pos, Quaternion quat, GameObject* target);
};

// EOF