/**
 * @file EnemyState
 * @brief 敵のステートマシン
 */
#include "EnemyState.h"
#include "EnemyCtrl.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "collision.h"

/**
 * @struct 待機
 */
struct IDOL : public State<EnemyState>
{
	EnemyStateMachine& m_machine;
	IDOL(EnemyStateMachine &machine) :State<EnemyState>(EnemyState::E_ENEMY_IDOL), m_machine(machine) {}
};

/**
 * @struct 移動
 */
struct MOVE : public State<EnemyState>
{
	EnemyStateMachine& m_machine;
	EnemyCtrl* m_ctrl;
	MOVE(EnemyStateMachine &machine) :State<EnemyState>(EnemyState::E_ENEMY_MOVE), m_machine(machine) {}

	void Init()
	{
		m_ctrl = m_machine.m_Parent->GetComponent<EnemyCtrl>();
	}

	void Update()
	{
		m_ctrl->GotoNoneTower();
		m_machine.Check();
	}
};

/**
 * @struct 移動
 */
struct FIGHT : public State<EnemyState>
{
	EnemyStateMachine& m_machine;
	EnemyCtrl* m_ctrl;
	FIGHT(EnemyStateMachine &machine) :State<EnemyState>(EnemyState::E_ENEMY_FIGHT), m_machine(machine) {}

	void Init()
	{
		m_ctrl = m_machine.m_Parent->GetComponent<EnemyCtrl>();
	}

	void Update()
	{
		m_ctrl->Attack(m_machine.GetTarget());
		m_machine.Check();
	}
};

/**
 * @brief 初期化処理
 * @return なし
 */
void EnemyStateMachine::Awake()
{
	m_playerObj = nullptr;
	SetState();
	GoToState(E_ENEMY_MOVE);
}

HRESULT EnemyStateMachine::Init()
{
	StateMachine::Init();
	m_playerObj = ObjectManager::GetInstance().FindWithTag(OBJ_TAG_PLAYER);

	return E_NOTIMPL;
}

/**
 * @brief ステートをリストにセット
 *@return なし
 */
void EnemyStateMachine::SetState()
{
	AddState(std::make_shared<IDOL>(*this));
	AddState(std::make_shared<MOVE>(*this));
	AddState(std::make_shared<FIGHT>(*this));
}

/**
 * @brief ステートの遷移先の確認
 * @return なし
 * @details 現在の状態を確認しステートの遷移を行う
 */
void EnemyStateMachine::Check()
{
	// プレイヤーが一定の距離にいたら攻撃する
	if (MyMath::Distance(m_Parent->GetTransform().position, m_playerObj->GetTransform().position) <= 300)
	{
		GoToState(EnemyState::E_ENEMY_FIGHT);
	}
	else
	{
		GoToState(EnemyState::E_ENEMY_MOVE);
	}
}

GameObject * EnemyStateMachine::GetTarget()
{
	return m_playerObj;
}

// EOF