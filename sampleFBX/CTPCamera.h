/**
 * @file CTPCamera.h
 * @brief OlÌƒJƒƒ‰
 */
#pragma once
#include "CCamera.h"

class Transform;

class CTPCamera :public CCamera
{
public:
	HRESULT Init();
	void Uninit();
	void Update();/*
	void SetTransform(Transform* transform);*/
};

// EOF