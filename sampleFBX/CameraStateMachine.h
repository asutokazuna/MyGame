/**
 * @file CameraStateMachine
 * @brief 使用するカメラの管理コンポーネント
 */
#pragma once
#include "StateMachine.h"

class CTPCamera;
class DeadCamera;
class GameObject;

enum CAMERA_STATE
{
	E_CAMERA_DEFAULT,
	E_CAMERA_PLAYER,
	E_CAMERA_DEAD,
};

/**
 * @class CameraStateMachine
 * @brief 使用するカメラの管理コンポーネント
 */
class CameraStateMachine :public StateMachine<CAMERA_STATE>
{
private:
	CTPCamera * m_tpCamera;
	DeadCamera* m_deadCamera;
	GameObject* m_player;
public:
	CameraStateMachine() : m_deadCamera(nullptr), m_tpCamera(nullptr) ,m_player(nullptr) {}
	void Awake();
	HRESULT Init();
	void SetState();
	CTPCamera* GetTPCamera();
	DeadCamera* GetDeadCamera();
	GameObject* GetPlayer();
};

// EOF