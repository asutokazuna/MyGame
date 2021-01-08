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

/**
 * @class CollisionManager
 * @brief 当たり判定管理クラス
 */
class CollisionManager:public Singleton<CollisionManager>
{
private:
	static std::unordered_map<int, Collision*> m_List;	//!< コライダーリスト
	static LinerOctreeManager<Collision> m_CollisionTree;
public:
	friend class Singleton<CollisionManager>;		//!< シングルトンクラスでの生成を可能に

	void Init();

	/**
	 * @breif リストにある全てのオブジェクトが当たっているか判定する
	 * @return なし
	 */
	void Check();

	void Set(Collision* col);

	void Delete(Collision* col);

	/**
	 * @breif バウンディングボックスでの当たり判定の比較
	 * @return 当たっていればtrue
	 */
	//static bool CheckBox(Vector3 mypos, Vector3 halfsize, Vector3 othorPos, Vector3 othorhalsize);

	static bool CheckOBB(const Transform& myObj, const Transform& othorObj);

	static Vector3 GetSize(const Transform& trans);

	/**
	 * @breif 当たり判定のリストの初期化
	 * @return なし
	 */
	static void Clear();
};

// EOF