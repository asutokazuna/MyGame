/**
 * @file TitleStateMachine.h
 * @brief タイトルのステートマシン
 */
#pragma once
#include "StateMachine.h"

enum TITLE_STATE
{
	E_TITLE_STATE_IDOL,
	E_TITLE_STATE_DEFAULT,
	E_TITLE_STATE_FD,
	E_TITLE_STATE_AVOID,
};


/**
 * @class TitleStateMachine
 */
class TitleStateMachine :public StateMachine<TITLE_STATE>
{
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