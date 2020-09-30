/**
 * @file FieldMesh
 * @brief 地面のメッシュクラス
 */
#pragma once
#include "Mesh.h"

/**
 * @class FieldMesh
 * @brief 床のメッシュ
 */
class FieldMesh :public Mesh
{
public:

	/**
	 * @brief 初期化
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 描画
	 * @return なし
	 */
	void Draw();
};

// EOF