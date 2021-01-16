/**
 * @file PlayerState.h
 * @brief プレイヤーのステートマシン
 */
#pragma once
#include "StateMachine.h"

class Transform;
class PlayerMove;
class PlayerCtrl;
class PlayerLifeCtrl;

enum PLAYER_STATE
{
	E_PLAYER_STATE_IDOL,
	E_PLAYER_STATE_DEFAULT,
	E_PLAYER_STATE_FD,
	E_PLAYER_STATE_AVOID,
	E_PLAYER_STATE_DEAD,

	E_PLAYER_STATE_MAX,
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
	PlayerLifeCtrl* m_life;

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
	
	/**
	 * @brief 更新処理
	 * @return なし
	 * @details 座標更新、当たり判定後の処理内容を記述する
	 */
	void LastUpdate();
};

// EOF