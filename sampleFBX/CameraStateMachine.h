#pragma once
#include "StateMachine.h"

enum CAMERA_STATE
{
	CAMERA_DEFAULT,
	CAMERA_PLAYER,
	CAMERA_DEAD,
};

class CameraStateMachine :public StateMachine<CAMERA_STATE>
{
public:
	void Awake();
	void SetState();
};

