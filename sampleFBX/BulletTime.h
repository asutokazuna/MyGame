/**
 * @file BulletTime
 * @breif バレットタイム風？カメラ
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