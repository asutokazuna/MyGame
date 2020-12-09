/**
 * @file TitleStateMachine.h
 * @brief タイトルのステートマシン
 */
#pragma once
#include "StateMachine.h"

enum TITLE_STATE
{
	E_TITLE_STATE_INIT,
	E_TITLE_STATE_FLY,
	E_TITLE_STATE_WAVE,
	E_TITLE_STATE_FADE,
	E_TITLE_STATE_ARRIVE,
	E_TITLE_STATE_IDOL,

	E_TITLE_STATE_MAX,
};

class TitleRogo;
class Rogo;

/**
 * @class TitleStateMachine
 */
class TitleStateMachine :public StateMachine<TITLE_STATE>
{
public:
	TitleRogo * m_clothRogo;
	Rogo* m_rogo;

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