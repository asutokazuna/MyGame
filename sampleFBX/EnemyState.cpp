/**
 * @file EnemyState
 * @brief 敵のステートマシン
 */
#include "EnemyState.h"

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
	MOVE(EnemyStateMachine &machine) :State<EnemyState>(EnemyState::E_ENEMY_MOVE), m_machine(machine) {}
};

/**
 * @brief 初期化処理
 * @return なし
 */
void EnemyStateMachine::Awake()
{
	SetState();
	GoToState(E_ENEMY_IDOL);
}

/**
 * @brief ステートをリストにセット
 *@return なし
 */
void EnemyStateMachine::SetState()
{
	AddState(std::make_shared<IDOL>(*this));
}

//