/**
 * @file CorePlayerGauge
 * @brief �R�A�̎c��HP�\���R���|�[�l���g
 */
#pragma once
#include "Component.h"

class ShaderInfo;
class CoreState;
class UIMesh;

/**
 * @class CorePlayerGauge
 * @brief �R�A�̎c��HP�\���R���|�[�l���g
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