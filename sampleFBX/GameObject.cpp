/**
 * @file GameObject.h
 * @brief �Q�[���I�u�W�F�N�g
 */
#include "GameObject.h"

/**
 * @brief �R���X�g���N�^
 */
GameObject::GameObject() {
	transform = AddComponent<Transform>();
}

/**
 * @brief �f�X�g���N�^
 */
GameObject::~GameObject() {
	for (auto com : m_ComponentList)
		delete com;

	//for (auto child : m_ChildList) {
	//	delete child;
	//}

}

/**
 * @brief �X�V����
 * @return  �Ȃ�
 */
void GameObject::Update()
{
	auto buff = m_ComponentList;
	for (auto com : buff)
		com->Update();
	
	for (auto& child : m_ChildList) {
		child->Update();
	}
}

/**
 * @brief �X�V����
 * @return  �Ȃ�
 */
void GameObject::LateUpdate()
{
	auto buff = m_ComponentList;
	for (auto com : buff)
		com->LateUpdate();

	for (auto& child : m_ChildList) {
		child->LateUpdate();
	}
}

/**
 * @brief �`�揈��
 * @return  �Ȃ�
 */
void GameObject::Draw()
{
	for (auto com : m_ComponentList)
		com->Draw();

	for (auto& child : m_ChildList) {
		child->Draw();
	}
}

/**
 * @brief �`�揈��
 * @return  �Ȃ�
 */
void GameObject::DrawAlpha()
{
	for (auto com : m_ComponentList)
		com->DrawAlpha();

	for (auto& child : m_ChildList) {
		child->DrawAlpha();
	}
}

/**
 * @brief �q�I�u�W�F�N�g�̐ݒ�
 * @return �Ȃ�
 */
 void GameObject::SetChild(GameObject * child)
 {
	 std::unique_ptr<GameObject> buff(child);

	 buff->Init();
	 m_ChildList.push_back(std::move(buff));
	 //child->Init();
	 //m_ChildList.push_back(child);
 }

 /**
  * @brief �g�����X�t�H�[���̎擾
  * @return �g�����X�t�H�[��
  */
 Transform& GameObject::GetTransform() {
	 return *transform;
 }

 /**
  * @brief �����蔻�菈��
  * @return �Ȃ�
  */
 void GameObject::OnCollisionEnter(GameObject * gameObbj)
 {
	 for (auto com : m_ComponentList)
		 com->OnCollisionEnter(gameObbj);

	 for (auto& child : m_ChildList) {
		 child->OnCollisionEnter(gameObbj);
	 }
 }

// EOF