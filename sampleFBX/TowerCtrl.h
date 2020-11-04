/**
 * @file TowerCtrl
 * @brief TowerCtrlクラス
 */
#pragma once
#include "Component.h"

// 前方宣言
struct TFbxMaterial;

/**
 * @class TowerCtrl
 * @brief タワーのパラメーター管理クラス
 */
class TowerCtrl: public Component
{
private:
	TFbxMaterial* material;

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 終了処理
	 * @return なし
	 */
	void Uninit();

	void Update();

	//void ChangeColor();

};

// EOF