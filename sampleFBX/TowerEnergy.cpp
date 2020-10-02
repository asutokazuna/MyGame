/**
 * @file TowerEnergy
 * @brief TowerEnergy�N���X
 */
#define _CRT_SECURE_NO_WARNINGS
#include "TowerEnergy.h"
#include "ImGui/imgui.h"
#include "GameObject.h"
#include "MissileMove.h"

static int num = 0;

/**
 * @brief �R���X�g���N�^
 */
TowerEnergy::TowerEnergy()
{
	m_Energy = ENERGY_MAX / 2;
	id = num;
	num++;
}

/**
 * @brief �`�揈��
 * @return �Ȃ�
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
 * @brief �G�l���M�[�̑���
 * @param num ����������l
 * @return �Ȃ�
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
 * @brief �G�l���M�[�̎擾
 * @return ���݂̃G�l���M�[
 */
int TowerEnergy::GetEnergy()
{
	return m_Energy;
}

/**
 * @brief �����蔻��
 * @param[in] ���������I�u�W�F�N�g
 * @return �Ȃ�
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