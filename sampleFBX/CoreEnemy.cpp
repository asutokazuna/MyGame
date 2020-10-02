/**
 * @file CoreEnemy.h
 * @brief 敵チームのコアクラス
 */
#include "CoreEnemy.h"
#include "CoreCollision.h"

#define CORE_POS_Z (600)

HRESULT CoreEnemy::Init()
{
	Core::Init();
	tag = OBJ_TAG_CORE_ENEMY;

	transform->position.z = CORE_POS_Z;

	return E_NOTIMPL;
}
