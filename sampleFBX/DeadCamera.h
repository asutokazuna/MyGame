/**
 * @file DeadCamera 
 * @brief プレイヤー死亡時のカメラオブジェクト
 */
#pragma once
#include "CCamera.h"

/**
 * @class DeadCamera 
 */
class DeadCamera :public CCamera
{
private:
	GameObject* m_player;
	float m_threshold;
	Vector3 m_startPos;
	Vector3 m_endPos;
public:
	//void Awake();
	HRESULT Init();
	//void Uninit();
	void LateUpdate();
};

// EOF