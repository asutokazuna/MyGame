/**
 * @file MissileCtrl
 * @brief �e�̐���R���|�[�l���g
 * @author Ariga
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
	GameObject* m_target;	//!< �Ǐ]�I�u�W�F�N�g

public:
	/**
	 * @brief ����������
	 * @return �Ȃ�
	 */
	virtual void Awake();

	HRESULT Init();

	/**
	 * @brief �X�V����
	 * @return �Ȃ�
	 */
	void Update();

	/**
	 * �e�̈З͂̎擾
	 * @return �e�̈З�
	 */
	virtual int GetPower();


	/**
	 * @brief �e�̔��ˏ���
	 * @param[in] pos ���ˍ��W
	 * @return �Ȃ�
	 */
	void Fire(Vector3* pos);

	/**
	 * @brief �e�̔��ˏ���
	 * @param[in] pos ���ˍ��W
	 * @param[in] quat ���˕���
	 * @return �Ȃ�
	 */
	void Fire(Vector3* pos, Quaternion quat);

	/**
	 * @brief �e�̔��ˏ���
	 * @param[in] pos ���ˍ��W
	 * @param[in] quat ���˕���
	 * @param[in] target �Ǐ]�I�u�W�F�N�g
	 * @return �Ȃ�
	 */
	void Fire(Vector3* pos, Quaternion quat, GameObject* target);
};

// EOF