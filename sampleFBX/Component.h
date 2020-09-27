/**
 * @file Component.h
 * @brief �R���|�[�l���g�I�u�W�F�N�g
 */
#pragma once
#include "Object.h"

class GameObject;

/**
 *@class Component
 * �R���|�[�l���g�N���X
 */
class Component : public Object
{
public:
	GameObject *m_Parent;	//!< �e�I�u�W�F�N�g

	/**
	 * @brief �R���X�g���N�^
	 */
	Component(){}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~Component(){}
	
	/**
	 * @brief �����蔻�菈��
	 * @return �Ȃ�
	 */
	virtual void OnCollisionEnter(GameObject* gameObbj){}

};

// EOF