#include "NumberDrawer.h"
#include "GameObject.h"
#include "DefaultShaderInfo.h"

NumberDrawer::NumberDrawer():num(0)
{
}

HRESULT NumberDrawer::Init()
{
	m_shader = m_Parent->GetComponent<DefaultShaderInfo>();

	m_shader->SetUV(Vector3(num / (float)10, 1, 1), Vector3(1 / (float)10, 1, 1));

	return S_OK;
}

void NumberDrawer::Draw()
{
}

void NumberDrawer::SetNumber(int num)
{
	this->num = num;
	m_shader->SetUV(Vector3(num / (float)10, 1, 0), Vector3(1 / (float)10, 1, 1));
}

// EOF