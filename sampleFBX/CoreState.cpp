/**
 * @file CoreState
 * @brief CoreStateƒNƒ‰ƒX
 */
#include "CoreState.h"
#include "imgui/imgui.h"

CoreState::CoreState():m_Life(30)
{
}

void CoreState::Draw()
{
#ifdef _DEBUG

	ImGui::Begin("CoreState");
	ImGui::SliderInt("Life", &m_Life, 0, 100);
	ImGui::End();

#endif // _DEBUG
}

int CoreState::GetLife()
{
	return m_Life;
}

void CoreState::AddLife(int value)
{
	m_Life += value;
}

void CoreState::SetLife(int Life)
{
	m_Life = Life;
}

// EOF