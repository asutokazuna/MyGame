/**
 * @file FieldMesh
 * @brief �n�ʂ̃��b�V���N���X
 */
#pragma once
#include "Mesh.h"

class FieldMesh :public Mesh
{
public:
	HRESULT Init();
	void Draw();
};

// EOF