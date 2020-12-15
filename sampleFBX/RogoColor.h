#pragma once
#include "GameObject.h"

class DefaultShaderInfo;
class Mesh;

class RogoColor :public GameObject
{
private:
	DefaultShaderInfo* m_shader;
	Mesh* m_mesh;
public:
	void Awake();
};

// EOF