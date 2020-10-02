/**
 * @file TowerEnergy
 * @brief TowerEnergyクラス
 */
#define _CRT_SECURE_NO_WARNINGS
#include "TowerEnergy.h"
#include "ImGui/imgui.h"
#include "GameObject.h"
#include "MissileMove.h"

static int num = 0;

/**
 * @brief コンストラクタ
 */
TowerEnergy::TowerEnergy()
{
	m_Energy = ENERGY_MAX / 2;
	id = num;
	num++;
}

/**
 * @brief 描画処理
 * @return なし
 */
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

/**
 * @brief エネルギーの増加
 * @param num 増加させる値
 * @return なし
 */
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

/**
 * @brief エネルギーの取得
 * @return 現在のエネルギー
 */
int TowerEnergy::GetEnergy()
{
	return m_Energy;
}

/**
 * @brief 当たり判定
 * @param[in] 当たったオブジェクト
 * @return なし
 */
void TowerEnergy::OnCollisionEnter(GameObject* othor)
{
	if (othor->CompareTag(OBJ_TAG_PLAYERMISSILE)) {
		AddEnergy(1);
		othor->GetComponent<MissileMove>()->m_nLife = 0;
	}
	if (othor->CompareTag(OBJ_TAG_ENEMYMISSILE)) {
		AddEnergy(-1);
		othor->GetComponent<MissileMove>()->m_nLife = 0;
	}
}
// EOF