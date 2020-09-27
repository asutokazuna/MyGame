/**
 * @file EnemyCtrl
 * @brief �G�̓����N���X
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