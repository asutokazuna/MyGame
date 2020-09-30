/**
 * @file PlayerMove
 * @brief プレイヤーの移動
 */
#include "PlayerMove.h"
#include "GameObject.h"
#include "input.h"
#include "MyMath.h"
#include "Transform.h"
#include "Rigidbody.h"

/**
 * @def 
 */
#define GRAVITY (0.98f)

static Rigidbody *rb;

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT PlayerMove::Init()
{
	m_Transform = &m_Parent->GetTransform();
	m_Transform->position.z = -500;

	rb = m_Parent->GetComponent<Rigidbody>();

	return S_OK;
}

/**
 * @brief 更新処理
 * @return なし
 */
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
	if (CInput::GetKeyTrigger(VK_SPACE)) {
		rb->AddForce({ 0,15,0 });
	}
}

// EOF