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
#include "PlayerLifeCtrl.h"
#include "ObjectManager.h"
#include "CharacterSpawnCtrl.h"

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
	float resist;
	const float MAX_SPEED = 5.0f;
	const float MIN_SPEED = 2.0f;
	
	void Move()
	{
		speed = Vector3();
		bool flg = false;


		// 前後左右
		if (CInput::GetKeyPress(VK_W)) {
			speed += Vector3(0, 0, 1);
			flg = true;
		}
		if (CInput::GetKeyPress(VK_S)) {
			speed += Vector3(0, 0, -1);
			flg = true;
		}
		if (CInput::GetKeyPress(VK_A)) {
			speed += Vector3(-1, 0, 0);
			flg = true;
		}
		if (CInput::GetKeyPress(VK_D)) {
			flg = true;
			speed += Vector3(1, 0, 0);
		}
		if (CInput::GetKeyPress(VK_LSHIFT)) {
			speed += Vector3(0, 1, 0);
			flg = true;
		}
		if (CInput::GetKeyPress(VK_LCONTROL)) {
			speed += Vector3(0, -1, 0);
			flg = true;
		}

		if (flg == true)
		{
			if (MAX_SPEED - MIN_SPEED > resist){
				resist += 0.1f;
			}
			speed = speed * (MAX_SPEED - resist);
		}
		else {
			resist = 0;
		}

		machine.m_move->AddMove(speed);
	}

	void Init()
	{
		resist = 0;
	}

	void Update() override
	{
		if (CInput::GetKeyPress(VK_L) || CInput::GetMouseButton(0)) {
			machine.m_ctrl->Attak();
		}

		Move();


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
	const float FD_SPEED = 7.0f;
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
	const float SPEED = 10.0f;
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
 * @struct 倒された時
 */
struct PLAYER_DEAD : public State<PLAYER_STATE>
{
	PlayerStateMachine& machine;
	CharacterSpawnCtrl* spawner;
	PLAYER_DEAD(PlayerStateMachine & _machine): State<PLAYER_STATE>(PLAYER_STATE::E_PLAYER_STATE_DEAD), machine(_machine){}

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Init()
	{
		spawner = ObjectManager::GetInstance().FindObject<GameObject>("CharacterSpawner")->GetComponent<CharacterSpawnCtrl>();
		spawner->Set(machine.m_Parent);
		machine.m_Parent->SetActive(false);
	}

	/**
	 * @brief 更新処理
	 * @return なし
	 */
	void Update()
	{
		// プレイヤーが生成された時
		if (spawner->IsExistence(machine.m_Parent) == false)
		{
			machine.GoToState(E_PLAYER_STATE_DEFAULT);
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
	m_life = m_Parent->GetComponent<PlayerLifeCtrl>();
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
	AddState(std::make_shared<PLAYER_DEAD>(*this));
}

/**
 * @brief 更新処理
 * @return なし
 * @details 座標更新、当たり判定後の処理内容を記述する
 */
void PlayerStateMachine::LastUpdate()
{
	StateMachine::LastUpdate();
	if (m_life->GetLife() <= 0)
	{
		GoToState(E_PLAYER_STATE_DEAD);
	}
}

// EOF