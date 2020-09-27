/**
 * @file CTPCamera.h
 * @brief 三人称カメラ
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