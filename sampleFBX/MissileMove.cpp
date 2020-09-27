/**
 * @file MissileMove
 * @brief ミサイルの動きクラス
 */
#include "MissileMove.h"
#include "GameObject.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
#define SPEED			(6.0f)

MissileMove::MissileMove() :m_nStat(0), m_nLife(0)
{
}

MissileMove::~MissileMove()
{
}

HRESULT MissileMove::Init()
{
	m_nLife = 0;
	m_nStat = 0;
	m_Speed = SPEED;

	m_transform = &m_Parent->GetTransform();

	return E_NOTIMPL;
}

void MissileMove::Update()
{
	// 未使用
	if (m_nStat == 0) {
		return;
	}
	// 追尾中(m_nStat == 1)
	--m_nLife;
	if (m_nLife <= 0) {
		m_nStat = 0;
		return;
	}

	m_transform->position += m_transform->GetForward() * m_Speed;
}

// EOF