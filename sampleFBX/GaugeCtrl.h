#pragma once
#include "Component.h"
#include "MyMath.h"

class LifeGauge;
class Transform;

class GaugeCtrl :public Component
{
private:
	GameObject* m_frame;
	LifeGauge*  m_LifeGauge;
	Vector3 m_offset;
	Transform* m_target;
public:
	void Awake();
	void Update();
	void SetPos(Vector3 pos);
	void SetSize(Vector3 size);
	void SetTarget(Transform* trans);
	void SetOffset(Vector3 offset);
};

// EOF