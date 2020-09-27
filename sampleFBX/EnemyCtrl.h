/**
 * @file EnemyCtrl
 * @brief “G‚Ì“®‚«ƒNƒ‰ƒX
 */
#pragma once
#include "Component.h"

class Transform;

class EnemyCtrl :public Component
{
private:
	Transform* m_transform;
public:
	EnemyCtrl();
	~EnemyCtrl();

	HRESULT Init();
	void Update();
};

// EOF