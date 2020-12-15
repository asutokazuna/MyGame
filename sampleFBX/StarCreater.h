#pragma once
#include "Component.h"

class StarParticle;

class StarCreater :public Component
{
private:
	StarParticle* m_star;
	int m_time;
public:
	StarCreater();
	~StarCreater();

	void Awake();
	HRESULT Init();
	void Update();
	void Draw();
	void Create();
	void Move();
};

// EOF