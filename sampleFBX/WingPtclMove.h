#pragma once
#include "Component.h"
#include "MyMath.h"

class WingPtclMove: public Component
{
private:
	Vector3 m_move;
	Vector3 m_rot;

public:;
	void Awake();
	void Update();
	void Create();
};

// EOF