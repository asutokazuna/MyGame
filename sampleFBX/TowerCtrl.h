/**
 * @file TowerCtrl
 * @brief TowerCtrl�N���X
 */
#pragma once
#include "Component.h"

// �O���錾
struct TFbxMaterial;

/**
 * @class TowerCtrl
 * @brief �^���[�̃p�����[�^�[�Ǘ��N���X
 */
class TowerCtrl: public Component
{
private:
	TFbxMaterial* material;

public:
	/**
	 * @brief ����������
	 * @return �Ȃ�
	 */
	void Awake();

	/**
	 * @brief �I������
	 * @return �Ȃ�
	 */
	void Uninit();

};

// EOF