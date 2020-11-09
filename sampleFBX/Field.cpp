/**
 * @file Field.cpp
 * @brief 地面クラス
 */
#include "Field.h"
#include "FieldMesh.h"
#include "collision.h"

/**
 * @brief 初期化
 * @return なし
 */
void Field::Awake()
{
	tag = OBJ_TAG_FIELD;
	m_Mesh = AddComponent<FieldMesh>();
	AddComponent<Collision>()->SetSize({ 15 * 80, 1, 15 * 80 })->SetPos({0,0,0});
}

 //EOF