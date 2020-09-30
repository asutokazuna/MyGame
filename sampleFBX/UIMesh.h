/**
 * @file UIMesh
 * @brief UIのメッシュクラス
 */
#pragma once
#include "Mesh.h"

/**
 * @class UIMesh
 * @brief UIに出すメッシュ
 */
class UIMesh :public Mesh
{
public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 描画処理
	 * @return なし
	 */
	void Draw();
};

// EOF