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
}

/**
 * @brief �`�揈��
 * @return  �Ȃ�
 */
void GameObject::Draw()
{
	for (auto com : m_ComponentList)
		com->Draw();
}

/**
 * @brief �`�揈��
 * @return  �Ȃ�
 */
void GameObject::DrawAlpha()
{
	for (auto com : m_ComponentList)
		com->DrawAlpha();
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
 }

 /**
  * @brief �g�����X�t�H�[���̎擾
  * @return �g�����X�t�H�[��
  */
 Transform& GameObject::GetTransform() {
	 return *transform;
 }

// EOF