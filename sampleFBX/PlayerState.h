/**
 * @file PlayerState.h
 * @brief プレイヤーのステートマシン
 */
#pragma once
#include "StateMachine.h"

class Transform;
class PlayerMove;
class PlayerCtrl;

enum PLAYER_STATE
{
	E_PLAYER_STATE_IDOL,
	E_PLAYER_STATE_DEFAULT,
	E_PLAYER_STATE_FD,
	E_PLAYER_STATE_AVOID,
};

/**
 * @class PlayerState
 */
class PlayerStateMachine:public StateMachine<PLAYER_STATE>
{
public:
	Transform * m_ParentTrans;
	PlayerMove* m_move;
	PlayerCtrl* m_ctrl;

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

private:
	/**
	 * @brief ステートをリストにセット
	 *@return なし
	 */
	void SetState();
};

// EOF