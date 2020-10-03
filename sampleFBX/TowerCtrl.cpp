/**
 * @file TowerCtrl
 * @brief TowerCtrlクラス
 */
#include "TowerCtrl.h"
#include "FbxModel.h"
/**
 * @brief 初期化処理
 * @return なし
 */
void TowerCtrl::Awake()
{
	material = new TFbxMaterial();
}

/**
 * @brief 終了処理
 * @return なし
 */
void TowerCtrl::Uninit()
{
	delete material;
}

// EOF