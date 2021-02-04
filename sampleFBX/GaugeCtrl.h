#pragma once
#include "Component.h"
#include "MyMath.h"

class LifeGauge;
class Transform;
class LifeGaugeShaderInfo;
class DefaultShaderInfo;

class GaugeCtrl :public Component
{
private:
	GameObject* m_frame;
	GameObject*  m_LifeGauge;
	Vector3 m_offset;
	Vector3 m_size;
	Transform* m_target;
public:
	void Awake();
	HRESULT Init();
	void Update();
	void SetPos(Vector3 pos);
	void SetSize(Vector3 size);
	void SetTarget(Transform* trans);
	void SetOffset(Vector3 offset);
	LifeGaugeShaderInfo * GetLifeShader();
	DefaultShaderInfo * GetBackShader();
};

// EOF