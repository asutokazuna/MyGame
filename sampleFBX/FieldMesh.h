/**
 * @file FieldMesh
 * @brief 地面のメッシュクラス
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