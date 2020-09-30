/**
 * @file Core.h
 * @brief ゲームの勝敗を決める核オブジェクトクラス
 */
#pragma once
#include "GameObject.h"

// 前方宣言
class CoreCollision;
class CoreState;

/**
 * @class Core
 * @brief 拠点のクラス
 */
class Core :public GameObject
{
protected:
	CoreCollision* m_Collision;
	CoreState* m_State;

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 現在HPの取得
	 * @return 現在のHP
	 */
	int GetLife();
};

// EOF