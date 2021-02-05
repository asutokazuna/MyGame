/**
 * @file ObjectRenderer
 * @brief オブジェクトの描画管理クラス
 */
#pragma once
#include "Singleton.h"
#include <vector>
#include "ObjectManager.h"

class GameObject;

class ObjectRenderer: public Singleton<ObjectRenderer>
{
public:
	friend class Singleton<ObjectRenderer>;		//!< シングルトンクラスでの生成を可能に

private:
	std::vector<GameObject*> m_2dObjVector;
	std::vector<GameObject*> m_3dObjVector;

public:
	void Init();
	void CreteData(std::vector<ObjectManager::HierarchyData>& data);
	void CreateDrawBuffer();
	void DrawShadow();
	void Draw();
};

// EOF