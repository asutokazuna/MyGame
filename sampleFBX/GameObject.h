/**
 * @file GameObject.h
 * @brief �R���|�[�l���g�I�u�W�F�N�g
 */
#pragma once
#include <list>
#include <memory>
#include "Component.h"
#include "Transform.h"
#include "Object.h"

/**
 * @class GameObject
 * @brief �Q�[���I�u�W�F�N�g
 */
class GameObject :public Object
{
protected:
	Transform *transform;			//!< �g�����X�t�H�[��

public:
	std::list<std::unique_ptr<GameObject>> m_ChildList;	//!< �q�I�u�W�F�N�g���X�g

public:
	std::list<Component*> m_ComponentList;		//!< �R���|�[�l���g���X�g

	/**
	 * @brief �R���X�g���N�^
	 */
	GameObject();

	/**
	 * @brief �f�X�g���N�^
	 */
	~GameObject() override;

	/**
	 * @brief �X�V����
	 * @return  �Ȃ�
	 */
	void Update();

	/**
	 * @brief �X�V����
	 * @return  �Ȃ�
	 */
	void LateUpdate() override;

	/**
	 * @brief �`�揈��
	 * @return  �Ȃ�
	 */
	void Draw() override;

	/**
	 * @brief �`�揈��
	 * @return  �Ȃ�
	 */
	void DrawAlpha() override;

	/**
	 * @brief �q�I�u�W�F�N�g�̐ݒ�
	 * @return �Ȃ�
	 */
	void SetChild(GameObject* child);

	/**
	 * @brief �g�����X�t�H�[���̎擾
	 * @return �g�����X�t�H�[��
	 */
	Transform& GetTransform();

	/**
 * @breif �R���|�[�l���g�̎擾
 * @return �N���X�̃R���|�[�l���g
 */
	template<class T>
	T* GetComponent()
	{
		for (auto com : m_ComponentList)
		{
			T* buff = dynamic_cast<T*>(com);
			if (buff != nullptr)
				return buff;
		}
		return nullptr;
	}

	/**
	 * @brief �R���|�[�l���g�̒ǉ�
	 * @return �ǉ������R���|�[�l���g�̎���
	 */
	template<class T>
	T* AddComponent()
	{
		T* buff = new T();
		buff->m_Parent = this;
		m_ComponentList.push_back(buff);
		buff->Awake();
		buff->Init();
		return buff;
	}
};

// EOF