#include "StarCreater.h"
#include "StarParticle.h"
#include "GameObject.h"
#include "StarMove.h"

#define MAX_STAR (20)
#define CREATE_TIME (30)

StarCreater::StarCreater()
{
	m_star = new StarParticle[MAX_STAR];
}


StarCreater::~StarCreater()
{
	delete[] m_star;
}

void StarCreater::Awake()
{
	for (int i = 0; i < MAX_STAR; i++)
	{
		m_star[i].Awake();
		m_star[i].SetActive(false);
	}
	m_time = 0;
}

HRESULT StarCreater::Init()
{
	for (int i = 0; i < MAX_STAR; i++)
	{
		m_star[i].Init();
	}
	return E_NOTIMPL;
}

void StarCreater::Update()
{
	for (int i = 0; i < MAX_STAR; i++)
	{
		if (m_star[i].GetActive() == true)
			m_star[i].Update();
	}

	m_time++;
	if (m_time > CREATE_TIME) {
		m_time = 0;
		Create();
	}
}

void StarCreater::Draw()
{
	for (int i = 0; i < MAX_STAR; i++)
	{
		if(m_star[i].GetActive() == true)
		m_star[i].Draw();
	}
}

void StarCreater::Create()
{
	for (int i = 0; i < MAX_STAR; i++)
	{
		if (m_star[i].GetActive() == true) {
			continue;
		}

		m_star[i].GetComponent<StarMove>()->Create();
		m_star[i].SetActive(true);
		break;
	}
}
