/**
 * @file Object.h
 * @brief �x�[�X�ƂȂ�I�u�W�F�N�g�N���X
 */
#include "Object.h"

void Object::Destroy(Object* obj) 
{
	//delete[] obj;
}

/**
 * @brief �f�X�g���N�^
 */
Object::~Object() {}

/**
 * @brief ����������
 */
void Object::Awake() {}

/**
 * @brief ����������
 * @return�@�Ȃ�
 */
HRESULT Object::Init() { return S_OK; }

/**
 * @brief �I������
 * @return�@�Ȃ�
 */
void Object::Uninit() {}

/**
 * @brief �X�V����
 * @return�@�Ȃ�
 */
void Object::Update() {}

/**
 * @brief �X�V����
 * @return�@�Ȃ�
 */
void Object::LateUpdate() {}

/**
 * @brief �`�揈��
 * @return�@�Ȃ�
 */
void Object::Draw() {}

/**
 * @brief ���������`�揈��
 * @return�@�Ȃ�
 */
void Object::DrawAlpha() {}

// EOF