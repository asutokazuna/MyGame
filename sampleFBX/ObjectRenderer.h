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
	std::vector<GameObject*> m_2dObjVector;			//!< 2Dオブジェクト描画用配列
	std::vector<GameObject*> m_3dObjVector;			//!< 3Dオブジェクト描画用配列
	std::vector<GameObject*> m_2dAlphaObjVector;	//!< 2D透明オブジェクト描画用配列
	std::vector<GameObject*> m_3dAlphaObjVector;	//!< 3D透明オブジェクト描画用配列
	std::vector<GameObject*> m_objVector;	//!< 描画しない部分の更新前処理用配列
	int m_objCnt;		//!< 描画するすべてのオブジェクト数

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

	/**
	 * @brief クリア処理
	 * @return なし
	 */
	void Clear();

private:
	/**
	 * @brief 描画用オブジェクトリスト作成する再帰関数
	 * @param[in] 描画リスト作成するヒエラルキーのデータ
	 * @return なし
	 */
	void CreteData(std::vector<ObjectManager::HierarchyData>& data);
};

// EOF