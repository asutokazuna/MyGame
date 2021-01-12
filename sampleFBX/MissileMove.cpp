/**
 * @file MissileMove
 * @brief ミサイルの動きクラス
 */
#include "MissileMove.h"
#include "GameObject.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
#define SPEED			(5.0f)

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT MissileMove::Init()
{
	m_Speed = SPEED;

	m_transform = &m_Parent->GetTransform();

	return E_NOTIMPL;
}

void MissileMove::Update()
{
	m_transform->position += m_transform->GetForward() * m_Speed;
}

// EOF