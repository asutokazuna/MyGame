/**
 * @file CameraStateMachine
 * @brief 使用するカメラの管理コンポーネント
 */
#include "CameraStateMachine.h"
#include "CTPCamera.h"
#include "DeadCamera.h"
#include "CPlayer.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "CCamera.h"
#include <memory>
#include "PlayerState.h"

/**
 * @struct 通常時
 */
struct CAMERA_PLAYER : public State<CAMERA_STATE>
{
	CameraStateMachine& machine;
	PlayerStateMachine* m_playerState;
	CAMERA_PLAYER(CameraStateMachine & _machine): State<CAMERA_STATE>(CAMERA_STATE::E_CAMERA_PLAYER), machine(_machine){}

	void Init()
	{
		machine.GetDeadCamera()->SetActive(false);
		CCamera::Set(machine.GetTPCamera());
		m_playerState = machine.GetPlayer()->GetComponent<PlayerStateMachine>();
	}

	void Update()
	{
		if (m_playerState->GetState() == E_PLAYER_STATE_DEAD)
		{
			machine.GoToState(E_CAMERA_DEAD);
		}
	}
};

/**
 * @struct プレイヤー死亡時
 */
struct CAMERA_DEAD : public State<CAMERA_STATE>
{
	CameraStateMachine& machine;
	PlayerStateMachine* m_playerState;
	CAMERA_DEAD(CameraStateMachine & _machine): State<CAMERA_STATE>(CAMERA_STATE::E_CAMERA_DEAD), machine(_machine){}

	void Init()
	{
		machine.GetDeadCamera()->Init();
		machine.GetTPCamera()->SetActive(false);
		CCamera::Set(machine.GetDeadCamera());
		m_playerState = machine.GetPlayer()->GetComponent<PlayerStateMachine>();
	}

	void Update()
	{
		if (m_playerState->GetState() == E_PLAYER_STATE_DEFAULT)
		{
			machine.GoToState(E_CAMERA_PLAYER);
		}
	}
};

/**
 * @brief 初期化処理
 * @return なし
 */
void CameraStateMachine::Awake()
{
	SetState();
}

/** 
 *@brief 初期化処理
 * @return なし
 */
HRESULT CameraStateMachine::Init()
{
	m_player = ObjectManager::GetInstance().FindObject<GameObject>("Player");
	m_tpCamera = m_Parent->GetChildTest("TPCamera");
	m_deadCamera = m_Parent->GetChildTest("DeadCamera");

	GoToState(E_CAMERA_PLAYER);
	StateMachine::Init();

	return E_NOTIMPL;
}

/**
 * @brief ステートをリストにセット
 *@return なし
 */
void CameraStateMachine::SetState()
{
	AddState(std::make_shared<CAMERA_PLAYER>(*this));
	AddState(std::make_shared<CAMERA_DEAD>(*this));
}

CTPCamera* CameraStateMachine::GetTPCamera()
{
	return dynamic_cast<CTPCamera*>( m_tpCamera);
}

DeadCamera* CameraStateMachine::GetDeadCamera()
{
	return dynamic_cast<DeadCamera*>(m_deadCamera);
}

GameObject* CameraStateMachine::GetPlayer()
{
	return m_player;
}

// EOF