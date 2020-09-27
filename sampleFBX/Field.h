#pragma once
#include "GameObject.h"

class FieldMesh;
class Field :public GameObject
{
private:
	FieldMesh* m_Mesh;
public:
	Field();
	~Field();

	HRESULT Init();
};

// EOF