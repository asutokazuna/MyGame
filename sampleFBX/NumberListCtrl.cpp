#include "NumberListCtrl.h"
#include "GameObject.h"
#include "DigitNumber.h"
#include "NumberDrawer.h"

void NumberListCtrl::Awake()
{
	m_width = 0;
}

HRESULT NumberListCtrl::Init()
{
	m_NumberList = m_Parent->GetChildren<DigitNumber>();

	return E_NOTIMPL;
}

void NumberListCtrl::SetNumber(int num)
{
	int work = num;
	int value = 0;

	for (auto obj : m_NumberList)
	{
		value = work % 10;
		obj->GetComponent<NumberDrawer>()->SetNumber(value);
		work /= 10;
	}
}

void NumberListCtrl::SetPos(Vector3 pos)
{
	int i = 0;
	Vector3 scale = Vector3();
	for (auto o : m_NumberList)
	{
		scale = o->GetTransform().scale;
		o->GetTransform().position = Vector3(pos.x - m_width * i, pos.y, pos.z);
		i++;
	}
}

void NumberListCtrl::SetWidth(float width)
{
	m_width = width;
}

// EOF