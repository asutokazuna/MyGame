/**
 * @file Billboard
 * @brief �r���{�[�h�N���X
 */
#pragma once
#include "Mesh.h"

class Billboard :public Mesh
{
public:
	HRESULT Init();
	void Draw();
};

// EOF