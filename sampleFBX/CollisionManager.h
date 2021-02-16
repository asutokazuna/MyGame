/**
 * @file CollisionManager
 * @brief 当たり判定管理クラス
 * @author Ariga
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
	LinerOctreeManager<Collision> m_CollisionTree;		//!< 当たり判定用八分木
	std::list<std::unique_ptr<TreeRegisterObject<Collision>>> m_registList;	//!< コリジョン登録オブジェクト
public:
	friend class Singleton<CollisionManager>;		//!< シングルトンクラスでの生成を可能に

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Init();

	/**
	 * @brief 終了処理
	 * @reutrn なし
	 */
	void Uninit();

	/**
	 * @brief 描画処理
	 * @return なし
	 */
	void Draw();

	/**
	 * @breif リストにある全てのオブジェクトが当たっているか判定する
	 * @return なし
	 */
	void Check();

	/**
	 * @brief コリジョンをを当たり判定管理リストにセット
	 * @param[in] col セットするコリジョンオブジェクト
	 * @return なし
	 */
	void Set(Collision* col);

	/**
	 * @brief コリジョンを当たり判定管理リストから削除
	 * @param[in] col コリジョンオブジェクト
	 * @return なし
	 */
	void Remove(Collision * col);

	/**
	 * @brief OBBの当たり判定確認処理
	 * @param[in] myObj 自分のトランスフォーム
	 * @param[in] othorObj 相手のトランスフォーム
	 * @param[in] myCol 自分のコリジョン
	 * @param[in] othorCol　相手のコリジョン
	 * @return 当たっていればtrue
	 */
	bool CheckOBB(const Transform & myObj, const Transform & othorObj, Collision * myCol, Collision * othorCol);

	/**
	 * @brief OBBのアルゴリズム
	 * @param[in] myObj　自分のトランスフォーム
	 * @param[in]
	 * @return 当たっていればtrue
	 */
	bool CheckOBB(const Transform& myObj, const Transform& othorObj);

	/**
	 * @brief オブジェクトのオフセットのサイズを取得(ただしサイズは半分の数値になっているので注意)
	 * @param[in] trans トランスフォーム
	 * @return サイズ
	 */
	static Vector3 GetSize(const Transform& trans);
};

// EOF