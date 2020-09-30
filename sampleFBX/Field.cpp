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
void Field::Awake()
{
	m_Mesh = AddComponent<FieldMesh>();
}

 //EOF