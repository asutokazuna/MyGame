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
#define FD_POWER (3.0f) 
#define WAIT_TIME (1 * 60)

static int mousePosX;
static int mousePosY;

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT PlayerMove::Init()
{
	m_Transform = &m_Parent->GetTransform();

	rb = m_Parent->GetComponent<Rigidbody>();
	mousePosX = CInput::GetMousePosition()->x;
	mousePosY = CInput::GetMousePosition()->y;

	return S_OK;
}

/**
 * @brief 更新処理
 * @return なし
 */
void PlayerMove::Update()
{
	Vector3 speed = Vector3(0,0,0);

	Rotate();

	if (CInput::GetKeyPress(VK_A)) {
		speed.x = -1.5f;
	}
	if (CInput::GetKeyPress(VK_D)) {
		speed.x = 1.5f;
	}
	if (CInput::GetKeyPress(VK_W)) {
		speed.z = 1.5f;
	}
	if (CInput::GetKeyPress(VK_S)) {
		speed.z = -1.2f;
	}

	FullDrive();

	// 座標更新
	m_Transform->position += m_Transform->GetForward() * speed.z + m_Transform->GetRight() * speed.x;

	// Ctrl
	if (CInput::GetKeyTrigger(VK_CONTROL)) {
		rb->AddForce({ 0,15,0 });		// ジャンプ
	}

	// 床との当たり判定
	if (m_Transform->position.y < 0) {
		m_Transform->position.y = 0;
	}
}

/**
 * @brief 高速移動
 *@return なし
 */
void PlayerMove::FullDrive()
{
	static int waitTime = 0;

	// SPACE
	if (CInput::GetKeyPress(VK_SPACE)) {
		waitTime++;
	}
	else {
		waitTime = 0;
		return;
	}

	if(waitTime < WAIT_TIME) {
		return;
	}

	m_Transform->position += m_Transform->GetForward() * FD_POWER;
}

/**
 * @brief 視点移動
 * @return なし
 */
void PlayerMove::Rotate()
{
	POINT mousePos = *CInput::GetMousePosition();

	angle.x = mousePos.x - mousePosX;
	angle.y = mousePos.y - mousePosY;

	mousePosX = mousePos.x;
	mousePosY = mousePos.y;

	m_Transform->AngleAxis(Transform::AXIS_WORLD_Y, MyMath::AngleToRadian(angle.x));
	
	m_Transform->AngleAxis(Transform::AXIS_X, MyMath::AngleToRadian(angle.y));
	
}

// EOF