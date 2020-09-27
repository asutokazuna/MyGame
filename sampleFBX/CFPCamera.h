/**
 * @file CTPCamera.h
 * @brief OlÌƒJƒƒ‰
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