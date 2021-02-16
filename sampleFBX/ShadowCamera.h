#pragma once
#include "CCamera.h"

class ShadowCamera :public CCamera
{
public:
	void Awake();
	void Draw();
};

// EOF