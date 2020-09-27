/**
 * @file UIMesh
 * @brief UIのメッシュクラス
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