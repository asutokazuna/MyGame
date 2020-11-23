/**
 * @file EnemyState.h
 * @brief 敵のステートマシン
 */
#pragma once
#include "StateMachine.h"
#include <memory>

struct IDOL;
struct MOVE;

enum EnemyState {
	E_ENEMY_IDOL,
	E_ENEMY_MOVE,
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
};

// EOF