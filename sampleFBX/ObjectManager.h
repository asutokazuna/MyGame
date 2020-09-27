/*
 *@file ObjectManager.h
 * @brief �I�u�W�F�N�g�Ǘ��N���X
 */
#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <memory>
#include "GameObject.h"

class Object;

/*
 *@class objectManager
 * @brief �I�u�W�F�N�g�Ǘ��N���X
 */
class ObjectManager : public Singleton<ObjectManager>
{
public:
	friend class Singleton<ObjectManager>;		//!< �V���O���g���N���X�ł̐������\��

private:
	std::unordered_map<std::string, std::unique_ptr<Object>> m_ObjList;
	std::unordered_map<std::string, std::unique_ptr<Object>> m_DontDestroyObjList;    // ���Ƃł��

public:

	/**
	 * @brief �I�u�W�F�N�g�̐���
	 * @param[in] name �I�u�W�F�N�g��
	 * @return ���������I�u�W�F�N�g�̎���
	 */
	template <class T>
	static T* Create(std::string name)
	{
		std::unique_ptr<T> work(new T());

		ObjectManager::GetInstance().m_ObjList[name] = std::move(work);
		return dynamic_cast<T*>(ObjectManager::GetInstance().m_ObjList[name].get());
	}

	/**
	 * @brief �I�u�W�F�N�g�̎擾
	 * @param[in] name �擾�������I�u�W�F�N�g�̖��O
	 * @retrun �I�u�W�F�N�g�̃|�C���^
	 */
	template <class T>
	static T* FindObject(std::string name)
	{
		return dynamic_cast<T*>(ObjectManager::GetInstance().m_ObjList[name].get());
	}

	/**
	 * @breif �I�u�W�F�N�g���X�g�̃N���A
	 * @return �Ȃ�
	 */
	static void Clear()
	{
		ObjectManager::GetInstance().m_ObjList.clear();
	}

	/**
	 * @brief ����������
	 * @return�@�Ȃ�
	 */
	static HRESULT Init();

	/**
	 * @brief �I������
	 * @return�@�Ȃ�
	 */
	static void Uninit();

	/**
	 * @brief �X�V����
	 * @return�@�Ȃ�
	 */
	static void Update();
	
	/**
	 * @brief �`�揈��
	 * @return�@�Ȃ�
	 */
	static void Draw();

};

// EOF