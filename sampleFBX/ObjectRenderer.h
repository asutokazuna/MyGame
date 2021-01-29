/**
 * @file ObjectRenderer
 * @brief オブジェクトの描画管理クラス
 */
#pragma once
#include "Singleton.h"

class ObjectRenderer: public Singleton<ObjectRenderer>
{
public:
	friend class Singleton<ObjectRenderer>;		//!< シングルトンクラスでの生成を可能に
public:
	void Init();
	void DrawShadow();
	void Draw();
};

// EOF