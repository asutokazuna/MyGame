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
#include "collision.h"
#include "ObjectManager.h"
#include "ImGui/imgui.h"

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
	m_move = Vector3();
	m_isDelay = false;

	//rb = m_Parent->GetComponent<Rigidbody>();
	mousePosX = CInput::GetMousePosition()->x;
	mousePosY = CInput::GetMousePosition()->y;

	return S_OK;
}

static float grav = 0;

/**
 * @brief 更新処理
 * @return なし
 */
void PlayerMove::Update()
{
	if (m_delayTime > 0) {
		m_delayTime--;
		return;
	}
	m_move = Vector3();

	if (!CInput::GetKeyPress(VK_P)) {
		Rotate();
	}

	grav -= 0.01f;

	m_move.y += grav;

	// Ctrl
	if (CInput::GetKeyTrigger(VK_CONTROL)) {
		//rb->AddForce({ 0,15,0 });		// ジャンプ
	}
}

void PlayerMove::LateUpdate()
{
	// 座標更新
	//m_Transform->position += m_Transform->GetForward() * m_move.z + m_Transform->GetRight() * m_move.x;
	m_Transform->position += m_move;
	if (m_Transform->position.y < 0) {
		m_Transform->position.y = 0;
		grav = 0;
	}
}

void PlayerMove::Draw()
{
#ifdef _DEBUG
	//ImGui::Begin("PlayerMove");
	//ImGui::SliderFloat("m_move x", &m_move.x, -1000.0f, 500.0f);
	//ImGui::SliderFloat("m_move y", &m_move.y, -1000.0f, 500.0f);
	//ImGui::SliderFloat("m_move z", &m_move.z, -1000.0f, 500.0f);
	//ImGui::End();
#endif
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

	m_Transform->AngleAxis(Transform::AXIS_WORLD_Y, MyMath::AngleToRadian((float)angle.x));
	
	m_Transform->AngleAxis(Transform::AXIS_X, MyMath::AngleToRadian((float)angle.y));
	
}

/**
* @brief 高速移動
*@return なし
*/
void PlayerMove::FullDrive()
{
	m_isDelay = true;
	m_delayTime = WAIT_TIME;

	m_move += m_Transform->GetForward() * FD_POWER;
}

void PlayerMove::Avoid()
{
	m_delayTime = 20;

	m_Transform->position += m_Transform->GetRight() * 10;
}

/**
 * @brief 移動量のセット
 * @return なし
 */
void PlayerMove::SetMove(Vector3 move)
{
	m_move = m_Transform->GetForward() * move.z + m_Transform->GetRight() * move.x;
}
/**
 * @brief 移動量のセット
 * @return なし
 */
void PlayerMove::SetMove(Vector3 move, Quaternion quat)
{
	Vector3 forward = { 0,0,1 };
	Vector3 right = { 1,0,0 };

	forward = MyMath::PosxQuaternion(forward, quat);
	right = MyMath::PosxQuaternion(right, quat);

	m_move = forward * move.z + right * move.x;
}

/**
 * @brief 移動量の加算
 * @return なし
 */
void PlayerMove::AddMove(Vector3 move)
{
	m_move = m_move + (m_Transform->GetForward() * move.z) + (m_Transform->GetRight() * move.x) + (m_Transform->GetUp() * move.y);
}

/**
 * @brief 移動量の加算
 * @return なし
 */
void PlayerMove::AddMove(Vector3 move, Quaternion quat)
{
	Vector3 forward = { 0,0,1 };
	Vector3 right = { 1,0,0 };

	forward = MyMath::PosxQuaternion(forward, quat);
	right = MyMath::PosxQuaternion(right, quat);

	m_move = m_move + (forward * move.z) + (right * move.x);
}

/**
 * @brief 当たり判定処理
 * @return なし
 */
void PlayerMove::OnCollisionEnter(GameObject* gameObj)
{
	if (gameObj->CompareTag(OBJ_TAG_FIELD))
	{
		//->position.y = gameObbj->GetTransform().position.y;// +m_Transform->scale.y;
	}
}

// EOF