/**
 * @file DebugBox.h
 * @brief デバッグの箱表示
 */
#pragma once
#include "Component.h"

/**
 * @class DebugBox 
 */
class DebugBox :public Component
{
public:
	void Awake();
	void Update();
	void Draw();
};

// EOF