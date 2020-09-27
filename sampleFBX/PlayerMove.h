/**
 * @file PlayerMove
 * @brief プレイヤーの移動
 */
#pragma once
#include "Component.h"

class Transform;
class PlayerMove: public Component
{
private:
	Transform* m_Transform;
public:
	HRESULT Init();
	void Update();
};

// EOF