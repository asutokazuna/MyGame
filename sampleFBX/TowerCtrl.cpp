/**
 * @file TowerCtrl
 * @brief TowerCtrl�N���X
 */
#include "TowerCtrl.h"
#include "FbxModel.h"
/**
 * @brief ����������
 * @return �Ȃ�
 */
void TowerCtrl::Awake()
{
	material = new TFbxMaterial();
}

/**
 * @brief �I������
 * @return �Ȃ�
 */
void TowerCtrl::Uninit()
{
	delete material;
}

// EOF