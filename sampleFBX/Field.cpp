/**
 * @file Field.cpp
 * @brief �n�ʃN���X
 */
#include "Field.h"
#include "FieldMesh.h"

/**
 * @brief ������
 * @return �Ȃ�
 */
HRESULT Field::Init()
{
	m_Mesh = AddComponent<FieldMesh>();

	return S_OK;
}

 //EOF