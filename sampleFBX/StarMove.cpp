/**
 * @file StarMove
 * @brief 星のエフェクトの動き
 */
#include "StarMove.h"
#include "Transform.h"
#include "GameObject.h"
#include "ShaderInfo.h"
#include "Mesh.h"
#include "ObjectManager.h"

/** 
 * @def
 */
#define MAX_ROT_SPEED (5)
#define LIFE_TIME (180)
	
/**
 * @brief 初期化
 * @retrun なし
 */
void StarMove::Awake()
{
	m_parentTrans = &m_Parent->GetTransform();
	m_size = m_parentTrans->scale;
	m_time = 0;
}

/**
 * @brief 移動処理
 * @return なし
 */
void StarMove::Move()
{
	m_parentTrans->position += m_move;
	m_time++;
}

/**
 * @brief 生成時処理
 * @param[in] pos 生成座標
 * @return なし
 */
void StarMove::Create(Vector3 pos)
{
	m_parentTrans->position = pos;
	m_move.x = (rand() % 10  - 5)/ (float)10;
	m_move.y = -rand() % 10 / (float)10 - 0.5f;
	m_size = (rand() % 10 -5) / (float)10;
	m_parentTrans->scale = Vector3(200, 200, 0) * m_size;
	float a = (rand() % 4 / (float)10) + 0.2f;
	m_backshader->ChangeAlpha(a);
	m_time = 0;
}

/**
 * @brief ライフ確認
 * @return 生存時間を過ぎていれば
 */
bool StarMove::IsLife()
{
	return m_time > 180 ? true : false;
}

// EOF