/**
 * @file FieldMesh
 * @brief �n�ʂ̃��b�V���N���X
 */
#pragma once
#include "Mesh.h"

/**
 * @class FieldMesh
 * @brief ���̃��b�V��
 */
class FieldMesh :public Mesh
{
public:

	/**
	 * @brief ������
	 * @return �Ȃ�
	 */
	HRESULT Init();

	/**
	 * @brief �`��
	 * @return �Ȃ�
	 */
	void Draw();
};

// EOF