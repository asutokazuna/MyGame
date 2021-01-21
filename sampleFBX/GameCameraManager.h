/**
 * @file GameCameraManager .h
 * @brief ゲームシーンのカメラ管理オブジェクト
 */
#pragma once
#include "GameObject.h"

/**
 * @class GameCameraManager 
 * @brief ゲームシーンのカメラを精選管理するクラス
 */
class GameCameraManager :public GameObject
{
public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 終了処理
	 * @return なし
	 */
	void Uninit();
};

// EOF