/**
 * @file EnemyCtrl
 * @brief “G‚Ì“®‚«ƒNƒ‰ƒX
 */
#include "EnemyCtrl.h"
#include "GameObject.h"

EnemyCtrl::EnemyCtrl()
{
}

EnemyCtrl::~EnemyCtrl()
{
}

HRESULT EnemyCtrl::Init()
{
	m_transform = &m_Parent->GetTransform();
	m_transform->position.z = 500;
	m_transform->AngleAxis(Transform::AXIS_Y, MyMath::AngleToRadian(180));


	return E_NOTIMPL;
}

void EnemyCtrl::Update()
{
	//m_transform->position += m_transform->GetForward();
}

// EOF