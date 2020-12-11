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
	m_alpha = 1;
	m_add = -0.01f;
	m_rot = (rand() % MAX_ROT_SPEED + 1) / 50.0f;
	m_color = Vector3();
	m_time = 0;
}
	
/**
 * @brief 初期化
 * @retrun なし
 */
HRESULT StarMove::Init()
{
	m_rogoSize = ObjectManager::GetInstance().FindObject<GameObject>("Rogo")->GetTransform().scale;

	return E_NOTIMPL;
}
	
/**
 * @brief 更新
 * @retrun なし
 */
void StarMove::Update()
{
	m_time++;
	m_parentTrans->rotation.z += m_rot;
	if (m_alpha >= 1) {
		m_add = -0.01f;
	}
	else if (m_alpha <= 0) {
		m_add = +0.01f;
	}
	m_alpha += m_add;
	m_backshader->ChangeAlpha(0.8f);

	if (m_time < LIFE_TIME / 2)
	{
		m_parentTrans->scale = m_size * (((float)m_time / LIFE_TIME) * 2);
	}
	else if (m_time >= LIFE_TIME / 2) {
		m_parentTrans->scale = m_size - m_size * ((( (float)m_time - LIFE_TIME / (float)2 )/ LIFE_TIME));
	}


	if (m_time > LIFE_TIME) {
		m_Parent->SetActive(false);
	}
}
	
/**
 * @brief 生成時処理
 * @retrun なし
 */
void StarMove::Create()
{
	m_rot = (rand() % MAX_ROT_SPEED + 1) / 120.0f;
	int posX = rand() % 300 - 100;
	int posY = rand() % 200 - 50;
	if (posX % 2 == 0) {
		posX += m_rogoSize.x / 2;
	}
	else {
		posX -= m_rogoSize.x / 2;
	}
	if (posY % 2 == 0) {
		posY += m_rogoSize.y / 2;
	}
	else {
		posY -= m_rogoSize.y / 2;
	}

	m_parentTrans->position = Vector3(posX, posY, 0);
	m_parentTrans->rotation = Vector3();

	float r, g, b;
	r = rand() % 50 / 50.0f;
	g = rand() % 50 / 50.0f;
	b = rand() % 50 / 50.0f;

	m_color = Vector3(r, g, b);
	m_backshader->ChangeColor(m_color);
	m_time = 0;
	m_parentTrans->scale = Vector3();
}

// EOF