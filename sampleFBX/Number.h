/**
 * @file 
 */
#pragma once
#include "GameObject.h"

class Mesh;
class ShaderInfo;

/** 
 * @class Number
 * @brief 数字1桁表示オブジェクト
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