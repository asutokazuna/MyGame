/**
 * @file CorePlayerGauge
 * @brief コアの残りHP表示コンポーネント
 */
#pragma once
#include "Component.h"

class ShaderInfo;
class CoreState;
class UIMesh;

/**
 * @class CorePlayerGauge
 * @brief コアの残りHP表示コンポーネント
 */
class CoreGauge :public Component
{
protected:
	UIMesh* m_mesh;
	ShaderInfo* m_shader;
	CoreState* m_state;
public:
	virtual void Awake();
	virtual void Update();
};

// EOF