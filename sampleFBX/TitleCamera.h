#pragma once
#include "CCamera.h"

class TitleCamera :public CCamera
{
public:
	void Awake();
	void Uninit();
	void Update();
};

// EOF