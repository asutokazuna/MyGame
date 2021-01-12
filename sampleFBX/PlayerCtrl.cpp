/**
 * @file PlayerCtrl
 * @brief プレイヤーの制御クラス
 */
#include "PlayerCtrl.h"
#include "input.h"
#include "Transform.h"
#include "GameObject.h"
#include "Weapon.h"
#include "WeaponCtrl.h"
#include "Geometry.h"
#include "PlayerShotDir.h"
#include "PlayerMove.h"

#define WAIT_TIME (1 * 60)

/**
 * @brief 初期化処理
 * @return なし
 */
void PlayerCtrl::Awake()
{
	m_Weapon = m_Parent->GetChild<Weapon>();
}

static Quaternion dir;
GameObject* target;
/**
 * @brief 更新処理
 * @return なし
 */
void PlayerCtrl::Update()
{
	dir = m_Parent->GetTransform().quaternion;
	target = m_Parent->GetComponent<PlayerShotDir>()->GetTarget();

	if (target != nullptr) {
		Vector3 targetdir = target->GetTransform().position - m_Parent->GetTransform().position;
		dir = MyMath::LookAt(targetdir);
	}

}
void PlayerCtrl::Draw()
{
#ifdef _DEBUG
	if (ImGui::TreeNode("shotDir")) {
		ImGui::SliderFloat("dir x", &dir.x, -1.0f, 1.0f);
		ImGui::SliderFloat("dir y", &dir.y, -1.0f, 1.0f);
		ImGui::SliderFloat("dir z", &dir.z, -1.0f, 1.0f);
		ImGui::TreePop();
	}
#endif
}

void PlayerCtrl::Attak()
{
	m_Weapon->GetComponent<WeaponCtrl>()->Shot(dir, target);
}

// EOF