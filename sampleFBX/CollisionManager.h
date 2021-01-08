/**
 * @file CollisionManager
 * @brief 当たり判定管理クラス
 */
#pragma once
#include "Singleton.h"
#include <unordered_map>
#include "LinerOctreeManager.h"
#include "collision.h"
#include "MyMath.h"
#include <list>
#include <memory>

/**
 * @class CollisionManager
 * @brief 当たり判定管理クラス
 */
class CollisionManager:public Singleton<CollisionManager>
{
private:
	LinerOctreeManager<Collision> m_CollisionTree;
	std::list<std::unique_ptr<TreeRegisterObject<Collision>>> m_registList;
public:
	friend class Singleton<CollisionManager>;		//!< シングルトンクラスでの生成を可能に

	void Init();

	void Uninit();

	/**
	 * @breif リストにある全てのオブジェクトが当たっているか判定する
	 * @return なし
	 */
	void Check();

	void Set(Collision* col);

	bool CheckOBB(const Transform & myObj, const Transform & othorObj, Collision * myCol, Collision * othorCol);
	
	/**
	 * @breif バウンディングボックスでの当たり判定の比較
	 * @return 当たっていればtrue
	 */
	//static bool CheckBox(Vector3 mypos, Vector3 halfsize, Vector3 othorPos, Vector3 othorhalsize);

	bool CheckOBB(const Transform& myObj, const Transform& othorObj);

	static Vector3 GetSize(const Transform& trans);
};

// EOF