/**
 * @file Field.cpp
 * @brief ’n–ÊƒNƒ‰ƒX
 */
#include "Field.h"
#include "FieldMesh.h"

/**
 * @brief ‰Šú‰»
 * @return ‚È‚µ
 */
HRESULT Field::Init()
{
	m_Mesh = AddComponent<FieldMesh>();

	return S_OK;
}

 //EOF