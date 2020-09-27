/**
 * @file Billboard
 * @brief ビルボードクラス
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