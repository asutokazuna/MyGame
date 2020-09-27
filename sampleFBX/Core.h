/**
 * @file Core.h
 * @brief �Q�[���̏��s�����߂�j�I�u�W�F�N�g�N���X
 */
#pragma once
#include "GameObject.h"

class CoreCollision;
class CoreState;

class Core :public GameObject
{
protected:
	CoreCollision* m_Collision;
	CoreState* m_State;
public:
	HRESULT Init();
	int GetLife();
};

// EOF