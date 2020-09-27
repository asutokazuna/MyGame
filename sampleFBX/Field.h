/**
 * @file Field.h
 * @brief 地面クラス
 */
#pragma once
#include "GameObject.h"

class FieldMesh;

/**
 * @class Field
 * @breif 地面
 */
class Field :public GameObject
{
private:
	FieldMesh* m_Mesh;		//!< 床のメッシュ

public:

	/**
	 * @brief 初期化
	 * @return なし
	 */
	HRESULT Init();
};

// EOF