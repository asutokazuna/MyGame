#pragma once
#include "Component.h"
#include "MyMath.h"

class Transform;

class WingPtclMove: public Component
{
private:
	Vector3 m_move;
	Vector3 m_rot;

	Transform* m_ParentTrans;
	Vector3 prevPosition0;
	Vector3 prevPosition1;

public:;
	void Awake();
	void Update();
	void Create(Vector3 velocity, Vector3 pos);
	void Move(Vector3 wind, Vector3 grabity, float resistance);
};

// EOF