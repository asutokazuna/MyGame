/**
 * @file PlayerMove
 * @brief プレイヤーの移動
 */
#include "PlayerMove.h"
#include "GameObject.h"
#include "input.h"
#include "MyMath.h"
#include "Transform.h"

HRESULT PlayerMove::Init()
{
	m_Transform = &m_Parent->GetTransform();
	m_Transform->position.z = -500;

	return S_OK;
}

void PlayerMove::Update()
{
	float speed = 0;

	if (CInput::GetKeyPress(VK_D)) {
		m_Transform->AngleAxis(Transform::AXIS_Y, MyMath::AngleToRadian(1));
	}
	if (CInput::GetKeyPress(VK_A)) {
		m_Transform->AngleAxis(Transform::AXIS_Y, MyMath::AngleToRadian(-1));
	}
	if (CInput::GetKeyPress(VK_W)) {
		speed = 1.5f;
	}
	if (CInput::GetKeyPress(VK_S)) {
		speed = -1.2f;
	}

	m_Transform->position += m_Transform->GetForward() * speed;
}

// EOF