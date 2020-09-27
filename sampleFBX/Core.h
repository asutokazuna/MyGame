/**
 * @file Core.h
 * @brief ゲームの勝敗を決める核オブジェクトクラス
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