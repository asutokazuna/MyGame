/**
 * @file TowerEnergy
 * @brief TowerEnergy�N���X
 */
#pragma once
#include "Component.h"

// def
#define ENERGY_MAX (20)

// �O���錾
class GameObject;

/**
 * @class TowerEnergy
 * @brief �^���[�̃p�����[�^�[
 */
class TowerEnergy :public Component
{
private:
	int m_Energy;
	int id;

public:
	/**
	 * @brief �R���X�g���N�^
	 */
	TowerEnergy();

	/**
	 * @brief �`�揈��
	 * @return �Ȃ�
	 */
	void Draw();

	/**
	 * @brief �G�l���M�[�̑���
	 * @param num ����������l
	 * @return �Ȃ�
	 */
	void AddEnergy(int num);

	/**
	 * @brief �G�l���M�[�̎擾
	 * @return ���݂̃G�l���M�[
	 */
	int& GetEnergy();

	/**
	 * @brief �G�l���M�[�̊������擾
	 * @return ���݂̊���
	 * @details 1�Ńv���C���[�̍ő�A-1�œG�̍ő�
	 */
	float GetEnergyPercent();

	/**
	 * @brief �����蔻��
	 * @param[in] ���������I�u�W�F�N�g
	 * @return �Ȃ�
	 */
	void OnCollisionEnter(GameObject* othor);
};

// EOF