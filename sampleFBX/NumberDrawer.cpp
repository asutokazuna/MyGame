/**
 * @file NumberDrawer
 * @brief 1�����\���R���|�[�l���g
 */
#include "NumberDrawer.h"
#include "GameObject.h"
#include "DefaultShaderInfo.h"

/**
 * @brief �R���X�g���N�^
 */
NumberDrawer::NumberDrawer():num(0)
{
}

/**
 * @brief ����������
 * @retrun �Ȃ�
 */
void NumberDrawer::Awake()
{
	m_shader = m_Parent->GetComponent<DefaultShaderInfo>();

	m_shader->SetUV(Vector3(num / (float)10, 1, 1), Vector3(1 / (float)10, 1, 1));
}

/**
 * @brief �����̃Z�b�g
 * @return �Ȃ�
 */
void NumberDrawer::SetNumber(int num)
{
	this->num = num;
	// UV�ړ�
	m_shader->SetUV(Vector3(num / (float)10, 1, 0), Vector3(1 / (float)10, 1, 1));
}

// EOF