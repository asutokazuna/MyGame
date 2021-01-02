/**
 * @file CoreState
 * @brief CoreStateƒNƒ‰ƒX
 */
#include "CoreState.h"
#include "imgui/imgui.h"

#define MAX_CORE_LIFE (50)

CoreState::CoreState():m_Life(MAX_CORE_LIFE)
{
}

void CoreState::Draw()
{
#ifdef _DEBUG
	if (ImGui::TreeNode("CoreState")) {
		ImGui::SliderInt("Life", &m_Life, 0, 100);
		ImGui::TreePop();
	}
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

float CoreState::GetPercent()
{
	return (float)m_Life / MAX_CORE_LIFE;
}

// EOF