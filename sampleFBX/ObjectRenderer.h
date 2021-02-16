/**
 * @file ObjectRenderer
 * @brief オブジェクトの描画管理クラス
 */
#pragma once
#include "Singleton.h"
#include <vector>
#include "ObjectManager.h"

// 前方宣言
class GameObject;

/**
 * @file ObjectRenderer
 * @brief オブジェクトの描画管理クラス
 */
class ObjectRenderer: public Singleton<ObjectRenderer>
{
public:
	friend class Singleton<ObjectRenderer>;		//!< シングルトンクラスでの生成を可能に

private:
	std::vector<GameObject*> m_2dObjVector;		//!< 2D描画用オブジェクト配列
	std::vector<GameObject*> m_3dObjVector;		//!< 3D描画用オブジェクト配列

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Init();

	/**
	 * @brief 描画オブジェクトリスト作成
	 * @return なし
	 */
	void CreateDrawBuffer();

	/**
	 * @brief 深度バッファシャドウの描画
	 * @return なし
	 */
	void DrawShadow();

	/**
	 * @brief 描画処理
	 * @return なし
	 */
	void Draw();

private:
	/**
	 * @brief 描画用オブジェクトリスト作成する再帰関数
	 * @param[in] 描画リスト作成するヒエラルキーのデータ
	 * @return なし
	 */
	void CreteData(std::vector<ObjectManager::HierarchyData>& data);
};

// EOF