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
#include "ShadowCamera.h"
#include "SceneManager.h"

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
void PlayerMove::Awake()
{
	m_ParentTransform->position = Vector3(0, 0, -500);
}

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT PlayerMove::Init()
{
	m_ParentTransform->position = Vector3(0, 0, -500);
	m_move = Vector3();
	m_isDelay = false;

	//rb = m_Parent->GetComponent<Rigidbody>();
	mousePosX = CInput::GetMousePosition()->x;
	mousePosY = CInput::GetMousePosition()->y;

	SceneManager::GetInstance().GetShadowCamera()->SetTarget(m_Parent);

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

	Rotate();


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
	//m_ParentTransform->position += m_ParentTransform->GetForward() * m_move.z + m_ParentTransform->GetRight() * m_move.x;
	m_ParentTransform->position += m_move;
	if (m_ParentTransform->position.y < 0) {
		m_ParentTransform->position.y = 0;
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

	float ax, ay;

	ax = (mousePos.x - mousePosX) / 2.0f;
	ay = (mousePos.y - mousePosY) / 1.0f;

	mousePosX = mousePos.x;
	mousePosY = mousePos.y;

	m_ParentTransform->AngleAxis(Transform::AXIS_WORLD_Y, MyMath::AngleToRadian((float)ax));
	
	m_ParentTransform->AngleAxis(Transform::AXIS_X, MyMath::AngleToRadian((float)ay));
	
}

/**
* @brief 高速移動
*@return なし
*/
void PlayerMove::FullDrive()
{
	m_isDelay = true;
	m_delayTime = WAIT_TIME;

	m_move += m_ParentTransform->GetForward() * FD_POWER;
}

/**
 * @brief 回避行動
 * @return なし
 */
void PlayerMove::Avoid()
{
	m_delayTime = 20;

	m_ParentTransform->position += m_ParentTransform->GetRight() * 10;
}

/**
 * @brief 移動量のセット
 * @return なし
 */
void PlayerMove::SetMove(Vector3 move)
{
	m_move = m_ParentTransform->GetForward() * move.z + m_ParentTransform->GetRight() * move.x;
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
	m_move = m_move + (m_ParentTransform->GetForward() * move.z) + (m_ParentTransform->GetRight() * move.x) + (m_ParentTransform->GetUp() * move.y);
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
		//->position.y = gameObbj->GetTransform().position.y;// +m_ParentTransform->scale.y;
	}
}

// EOF