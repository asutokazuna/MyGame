/**
 * @file EnemyState.h
 * @brief 敵のステートマシン
 */
#pragma once
#include "StateMachine.h"
#include <memory>

struct IDOL;
struct MOVE;

/**
 * @brief 敵の状態
 */
enum EnemyState {
	E_ENEMY_IDOL,
	E_ENEMY_MOVE,
	E_ENEMY_FIGHT,
};

/**
 * @class EnemyStateMachine
 * @biref 敵の状態管理
 */
class EnemyStateMachine:public StateMachine<EnemyState>
{
public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief ステートをリストにセット
	 *@return なし
	 */
	void SetState();

	/** 
	 * @brief ステートの遷移先の確認
	 * @return なし
	 * @details 現在の状態を確認しステートの遷移を行う
	 */
	void Check();
};

// EOF