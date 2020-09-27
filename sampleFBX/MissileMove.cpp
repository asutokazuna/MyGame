/**
 * @file MissileMove
 * @brief �~�T�C���̓����N���X
 */
#include "MissileMove.h"
#include "GameObject.h"

//*****************************************************************************
// �萔��`
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
	// ���g�p
	if (m_nStat == 0) {
		return;
	}
	// �ǔ���(m_nStat == 1)
	--m_nLife;
	if (m_nLife <= 0) {
		m_nStat = 0;
		return;
	}

	m_transform->position += m_transform->GetForward() * m_Speed;
}

// EOF