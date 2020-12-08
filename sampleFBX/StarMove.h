/**
 * @file StarMove
 * @brief 星のエフェクトの動き
 */
#pragma once
#include "Component.h"
#include "MyMath.h"

class Transform;
class ShaderInfo;

/**
 * @class StarMove
 * @brief 星のエフェクトの動き
 */
class StarMove :public Component
{
private:
	Transform * m_parentTrans;
	float m_rot;
	ShaderInfo* m_backshader;
	float m_alpha;
	float m_add;
	Vector3 m_color;
	Vector3 m_size;
	int m_time;
public:

	void Awake();

	HRESULT Init();

	void Update();
	void Create();
	void SetFrontMesh() {

	}

	void SetBackShader(ShaderInfo* shader) {
		m_backshader = shader;
	}
};

// EOF