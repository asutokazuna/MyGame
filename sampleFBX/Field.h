/**
 * @file Field.h
 * @brief �n�ʃN���X
 */
#pragma once
#include "GameObject.h"

class FieldMesh;

/**
 * @class Field
 * @breif �n��
 */
class Field :public GameObject
{
private:
	FieldMesh* m_Mesh;		//!< ���̃��b�V��

public:

	/**
	 * @brief ������
	 * @return �Ȃ�
	 */
	HRESULT Init();
};

// EOF