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
private:
	Vector3 m_pos;
	Vector3 m_oldPos;
	float m_threshold;
public:

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
	HRESULT Init();
	void Uninit();
	void LateUpdate();
	void Draw();
};

// EOF