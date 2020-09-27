/**
 * @file TowerEnergy
 * @brief TowerEnergyƒNƒ‰ƒX
 */
#define _CRT_SECURE_NO_WARNINGS

#include "TowerEnergy.h"
#include "ImGui/imgui.h"

static int num = 0;

TowerEnergy::TowerEnergy()
{
	m_Energy = ENERGY_MAX / 2;
	id = num;
	num++;
}

TowerEnergy::~TowerEnergy()
{
}

void TowerEnergy::Draw()
{
#ifdef _DEBUG
	ImGui::Begin("Tower");
	char str[50];
	sprintf(str, "Energy%d", id);
	ImGui::SliderInt(str, &m_Energy, 0, 500);
	ImGui::End();
#endif
}

void TowerEnergy::AddEnergy(int num)
{
	m_Energy += num;
	if (m_Energy < 0) {
		m_Energy = 0;
	}
	else if (m_Energy > ENERGY_MAX) {
		m_Energy = ENERGY_MAX;
	}
}

int TowerEnergy::GetEnergy()
{
	return m_Energy;
}

// EOF