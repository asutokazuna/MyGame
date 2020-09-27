/**
 * @file MissileMove
 * @brief �~�T�C���̓����N���X
 */
#pragma once
#include "Component.h"

class Transform;

class MissileMove :public Component
{
private:
	Transform* m_transform;
public:
	int m_nStat;			//!< 0:���g�p, 1:�g�p��
	int m_nLife;			//!< ����
	int m_Speed;
public:
	MissileMove();
	~MissileMove();

	HRESULT Init();
	void Update();
};

// EOF