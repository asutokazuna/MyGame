#include "Field.h"
#include "FieldMesh.h"

Field::Field()
{
}

Field::~Field()
{
}

HRESULT Field::Init()
{
	m_Mesh = AddComponent<FieldMesh>();

	return S_OK;
}

 //EOF