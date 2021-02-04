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

// 前方宣言
class TitleRogo;
class Rogo;
class TitleStart;
class RogoColor;

/**
 * @class TitleStateMachine
 * @brief タイトルの状態を管理するクラス
 */
class TitleStateMachine :public StateMachine<TITLE_STATE>
{
public:
	Rogo* m_rogo;				//!< タイトルロゴ
	TitleStart* m_startText;	//!< push start
	GameObject* m_particle;		//!< パーティクル
	RogoColor* m_rogoColor;		//!< 色付きタイトルロゴ

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	HRESULT Init();

private:
	/**
	 * @brief ステートをリストにセット
	 *@return なし
	 */
	void SetState();
};

// EOF