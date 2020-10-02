/**
 * @file CorePlayer.h
 * @brief �����`�[���̃R�A�N���X
 */
#include "CorePlayer.h"
#include "CoreCollision.h"

#define CORE_POS_Z (-600)

HRESULT CorePlayer::Init()
{
	Core::Init();

	transform->position.z = CORE_POS_Z;
	return E_NOTIMPL;
}

// EOF