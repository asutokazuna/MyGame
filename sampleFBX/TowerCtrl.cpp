/**
 * @file TowerCtrl
 * @brief TowerCtrlƒNƒ‰ƒX
 */
#include "TowerCtrl.h"
#include "FbxModel.h"
/**
 * @brief ‰Šú‰»ˆ—
 * @return ‚È‚µ
 */
void TowerCtrl::Awake()
{
	material = new TFbxMaterial();
}

/**
 * @brief I—¹ˆ—
 * @return ‚È‚µ
 */
void TowerCtrl::Uninit()
{
	delete material;
}

// EOF