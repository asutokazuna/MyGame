#include "NumberListCtrl.h"
#include "GameObject.h"
#include "DigitNumber.h"
#include "NumberDrawer.h"

/**
 * @brief ����������
 * @return �Ȃ�
 */
void NumberListCtrl::Awake()
{
	m_width = 35;
	m_NumberList = m_Parent->GetChildren<DigitNumber>();
}

/**
 * @brief ����������
 * @return �Ȃ�
 */
HRESULT NumberListCtrl::Init()
{

	return E_NOTIMPL;
}

/**
 * @brief �����̃Z�b�g
 * @param[in] �Z�b�g���鐔��
 * @return �Ȃ�
 */
void NumberListCtrl::SetNumber(int num)
{
	int work = num;
	int value = 0;

	for (auto obj : m_NumberList)
	{
		value = work % 10;
		obj->GetComponent<NumberDrawer>()->SetNumber(value);
		work /= 10;
	}
}

/**
 * @brief ���W�̐ݒ�
 * @param[in] pos �ݒ���W
 * @return �Ȃ�
 */
void NumberListCtrl::SetPos(Vector3 pos)
{
	int i = 0;
	Vector3 scale = Vector3();
	for (auto o : m_NumberList)
	{
		scale = o->GetTransform().scale;
		o->GetTransform().position = Vector3(pos.x - m_width * i, pos.y, pos.z);
		i++;
	}
}

/**
 * @brief �������m�̕��̐ݒ�
 * @param[in] width ��
 * @return �Ȃ�
 */
void NumberListCtrl::SetWidth(float width)
{
	m_width = width;
}

// EOF