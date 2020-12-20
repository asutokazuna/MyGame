#pragma once
#include "Component.h"

class DefaultShaderInfo;

/**
 * @class 
 * @brief 
 */
class NumberDrawer :public Component
{
private:
	int num;
	DefaultShaderInfo* m_shader;
public:
	NumberDrawer();
	HRESULT Init();
	void Draw();
	void SetNumber(int num);
};

// EOF