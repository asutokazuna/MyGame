/**
 * @file PlayerCollision
 * @brief PlayerCollisionƒNƒ‰ƒX
 */
#include "PlayerCollision.h"
#include "GameObject.h"
#include "ImGui/imgui.h"

static bool hit = false;

void PlayerCollision::Draw()
{
#ifdef _DEBUG
	ImGui::Begin("PlayerCollision");
	ImGui::Checkbox("hit", &hit);
	ImGui::SliderFloat("x", &m_transform->scale.x, 1, 500);
	ImGui::SliderFloat("y", &m_transform->scale.y, 1, 500);
	ImGui::SliderFloat("z", &m_transform->scale.z, 1, 500);
	ImGui::End();
	Collision::Draw();
#endif
}

// EOF