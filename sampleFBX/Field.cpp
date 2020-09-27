/**
 * @file Field.cpp
 * @brief 地面クラス
 */
#include "Field.h"
#include "FieldMesh.h"

/**
 * @brief 初期化
 * @return なし
 */
HRESULT Field::Init()
{
	m_Mesh = AddComponent<FieldMesh>();

	return S_OK;
}

 //EOF