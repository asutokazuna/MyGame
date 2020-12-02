/**
 * @file PlayerState.h
 * @brief プレイヤーのステートマシン
 */
#include "PlayerState.h"
#include <memory>
#include "GameObject.h"
#include "input.h"
#include "PlayerMove.h"
#include "PlayerCtrl.h"

/**
 * @struct 待機
 */
struct PLAYER_IDOL : public State<PLAYER_STATE>
{
	PlayerStateMachine& machine;
	PLAYER_IDOL(PlayerStateMachine & _machine): State<PLAYER_STATE>(PLAYER_STATE::E_PLAYER_STATE_IDOL), machine(_machine){}
};

/**
 * @struct 通常
 */
struct PLAYER_DEFAULT : public State<PLAYER_STATE>
{
	PlayerStateMachine& machine;
	PLAYER_DEFAULT(PlayerStateMachine & _machine) : State<PLAYER_STATE>(PLAYER_STATE::E_PLAYER_STATE_DEFAULT), machine(_machine) {}
	Vector3 speed;
	const float SPEED = 3.0f;

	void Update() override
	{
		speed = Vector3();

		if (CInput::GetKeyPress(VK_W)) {
			speed += Vector3(0, 0, SPEED);
		}
		if (CInput::GetKeyPress(VK_S)) {
			speed += Vector3(0, 0, -SPEED);
		}
		if (CInput::GetKeyPress(VK_A)) {
			speed += Vector3(-SPEED, 0, 0);
		}
		if (CInput::GetKeyPress(VK_D)) {
			speed += Vector3(SPEED, 0, 0);
		}

		if (CInput::GetKeyPress(VK_L) || CInput::GetMouseButton(0)) {
			machine.m_ctrl->Attak();
		}

		machine.m_move->AddMove(speed);

		if (CInput::GetKeyTrigger(VK_SPACE)) {
			machine.GoToState(PLAYER_STATE::E_PLAYER_STATE_FD);
		}
		else if (CInput::GetKeyTrigger(VK_Q) || CInput::GetKeyTrigger(VK_E)) {
			machine.GoToState(PLAYER_STATE::E_PLAYER_STATE_AVOID);
		}
	}
};

/**
 * @struct フルドライブ
 */
struct PLAYER_FD : public State<PLAYER_STATE>
{
	PlayerStateMachine& machine;
	PLAYER_FD(PlayerStateMachine & _machine) : State<PLAYER_STATE>(PLAYER_STATE::E_PLAYER_STATE_FD), machine(_machine) {}

	const int WAIT_TIME = 1 * 60;
	const float FD_SPEED = 5.0f;
	int m_waitTime;

	void Init() override
	{
		m_waitTime = WAIT_TIME;
	}

	void Update() override
	{
		m_waitTime--;

		if (m_waitTime > 0) {
			return;
		}

		Vector3 speed = Vector3(0, 0, FD_SPEED);

		if (CInput::GetKeyPress(VK_A)) {
			speed += Vector3(-1, 0, 0);
		}
		else if (CInput::GetKeyPress(VK_D)) {
			speed += Vector3(1, 0, 0);
		}

		if (CInput::GetKeyPress(VK_L) || CInput::GetMouseButton(0)) {
			machine.m_ctrl->Attak();
		}

		machine.m_move->AddMove(speed);

		if (CInput::GetKeyPress(VK_SPACE) == false) {
			machine.GoToState(PLAYER_STATE::E_PLAYER_STATE_DEFAULT);
		}
	}
};

/**
 * @brief 回避中
 */
struct PLAYER_AVOID : public State<PLAYER_STATE>
{
	PlayerStateMachine& machine;
	PLAYER_AVOID(PlayerStateMachine & _machine) : State<PLAYER_STATE>(PLAYER_STATE::E_PLAYER_STATE_AVOID), machine(_machine) {}
	Vector3 speed;
	const float SPEED = 5.0f;
	const int WAIT_TIME = 15;
	int m_waitTime;
	int dir;
	Quaternion quat;

	void Init() override
	{
		quat = machine.m_ParentTrans->quaternion;
		m_waitTime = WAIT_TIME;
		if (CInput::GetKeyPress(VK_E)) {
			dir = 1;
		}
		else if (CInput::GetKeyPress(VK_Q)) {
			dir = -1;
		}
	}

	void Update() override
	{
		speed = Vector3(SPEED, 0, 0) * (float)dir;

		machine.m_move->SetMove(speed, quat);

		if (m_waitTime-- < 0) {
			machine.GoToState(PLAYER_STATE::E_PLAYER_STATE_DEFAULT);
		}
	}
};

/**
 * @brief 初期化処理
 * @return なし
 */
void PlayerStateMachine::Awake()
{
	m_ParentTrans = &m_Parent->GetTransform();
	m_move = m_Parent->GetComponent<PlayerMove>();
	m_ctrl = m_Parent->GetComponent<PlayerCtrl>();
	SetState();
	GoToState(E_PLAYER_STATE_DEFAULT);
}

/**
 * @brief ステートをリストにセット
 *@return なし
 */
void PlayerStateMachine::SetState()
{
	AddState(std::make_shared<PLAYER_IDOL>(*this));
	AddState(std::make_shared<PLAYER_DEFAULT>(*this));
	AddState(std::make_shared<PLAYER_FD>(*this));
	AddState(std::make_shared<PLAYER_AVOID>(*this));
}

// EOF