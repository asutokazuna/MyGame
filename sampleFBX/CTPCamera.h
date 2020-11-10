/**
 * @file CTPCamera.h
 * @brief 三人称カメラ
 */
#pragma once
#include "CCamera.h"

class Transform;

/**
 * @class CTPCamera
 * @brief サードパーソンカメラ
 */
class CTPCamera :public CCamera
{
public:

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
	void Uninit();
	void Update();
};

// EOF