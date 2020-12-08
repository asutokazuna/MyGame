/**
 * @file StarParticle
 * @brief 星のエフェクト
 */
#pragma once
#include "GameObject.h"

class ShaderInfo;
class Mesh;

class StarParticle :public GameObject
{
private:
	ShaderInfo* m_shader;
	ShaderInfo* m_backshader;
	Mesh* m_mesh;
	Mesh* m_backmesh;
public:
	void Awake();
};

// EOF