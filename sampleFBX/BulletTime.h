/**
 * @file BulletTime
 * @breif �o���b�g�^�C�����H�J����
 */
#pragma once
#include "CCamera.h"

class CBulletTime :public CCamera
{
private:
	float m_fangle;
public:
	HRESULT Init();
	void Uninit();
	void Update();
};

// EOF