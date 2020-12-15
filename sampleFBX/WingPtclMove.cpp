#include "WingPtclMove.h"
#include "GameObject.h"

void WingPtclMove::Awake()
{
	m_move = Vector3();
}

void WingPtclMove::Update()
{
	m_Parent->GetTransform().position += m_move;
	m_Parent->GetTransform().rotation += m_rot;
}

void WingPtclMove::Create()
{
	const int MAX_MOVE = 5;

	m_move.x = rand() % MAX_MOVE / 10.0f;
	m_move.y = rand() % MAX_MOVE / 10.0f;
	m_move.z = rand() % MAX_MOVE / 10.0f;
	m_rot.x = rand() % MAX_MOVE / 20.0f;
	m_rot.y = rand() % MAX_MOVE / 20.0f;
	m_rot.z = rand() % MAX_MOVE / 20.0f;
}

// EOF