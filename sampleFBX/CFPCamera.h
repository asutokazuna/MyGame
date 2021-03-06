/**
 * @file CTPCamera.h
 * @brief 三人称カメラ
 */
#pragma once
#include "CCamera.h"

class CFPCamera :public CCamera
{
public:
	HRESULT Init();
	void Uninit();
	void Update();
};

// EOF