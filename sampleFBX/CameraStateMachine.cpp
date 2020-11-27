#include "CameraStateMachine.h"

/**
 * @struct 待機
 */
struct CAMERA_PLAYER : public State<CAMERA_STATE>
{
	CameraStateMachine& machine;
	CAMERA_PLAYER(CameraStateMachine & _machine): State<CAMERA_STATE>(CAMERA_STATE::CAMERA_PLAYER), machine(_machine){}
};

void CameraStateMachine::Awake()
{
}

void CameraStateMachine::SetState()
{
}
