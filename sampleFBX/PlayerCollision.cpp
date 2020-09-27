/**
 * @file PlayerCollision
 * @brief PlayerCollisionƒNƒ‰ƒX
 */
#include "PlayerCollision.h"
#include "GameObject.h"
#include "ImGui/imgui.h"

static bool hit = false;

void PlayerCollision::Check(Collision * othor)
{
	if (othor->GetTag() == COL_MISSILE) {
		//size.x = 1;
		hit = true;
		return;
	}
	hit = false;
}

HRESULT PlayerCollision::Init()
{
	m_tag = COL_PLAYER;
	size = { 25,25,25};
	pos = m_Parent->GetTransform().position;

	Collision::Init();

	return S_OK;
}

void PlayerCollision::Update()
{
	pos = m_Parent->GetTransform().position;
	Collision::Update();
}

void PlayerCollision::Draw()
{
#ifdef _DEBUG
	ImGui::Begin("PlayerCollision");
	ImGui::Checkbox("hit", &hit);
	ImGui::End();
	Collision::Draw();
#endif
}

// EOF