/**
 * @file UIMesh
 * @brief UI�̃��b�V���N���X
 */
#pragma once
#include "Mesh.h"

class UIMesh :public Mesh
{
public:
	HRESULT Init();
	void Draw();
};

// EOF