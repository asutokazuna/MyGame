/**
 * @file 
 */
#pragma once
#include "GameObject.h"

class Mesh;
class ShaderInfo;

/** 
 * @class Number
 * @brief ����1���\���I�u�W�F�N�g
 */
class Number :public GameObject
{
private:
	ShaderInfo* m_shader;
	Mesh* m_mesh;
public:
	void Awake();
};

// EOF