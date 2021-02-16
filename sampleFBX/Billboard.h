/**
 * @file Billboard
 * @brief ビルボードクラス
 * @author Ariga
 */
#pragma once
#include "Mesh.h"

/**
 * @class Billboard
 * @brief ビルボード
 */
class Billboard :public Mesh
{
public:
	/**
	 * @brief 初期化処理
	 * @return　なし
	 */
	void Awake();

	/**
	 * @brief 描画処理
	 * @return なし
	 */
	void Draw();
};

// EOF