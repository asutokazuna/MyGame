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
	E_TITLE_STATE_IDOL,
	E_TITLE_STATE_FADEOUT,
	E_TITLE_STATE_LEAVE,

	E_TITLE_STATE_MAX,
};

class TitleRogo;
class Rogo;
class TitleStart;

/**
 * @class TitleStateMachine
 */
class TitleStateMachine :public StateMachine<TITLE_STATE>
{
public:
	TitleRogo * m_clothRogo;
	Rogo* m_rogo;
	TitleStart* m_startText;
	GameObject* m_particle;

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