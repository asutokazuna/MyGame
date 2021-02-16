/*
 *@file ObjectManager.h
 * @brief オブジェクト管理クラス
 * @author Ariga
 */
#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <memory>
#include "GameObject.h"
#include <list>
#include <vector>
#include <string>

/*
 *@class objectManager
 * @brief オブジェクト管理クラス
 */
class ObjectManager : public Singleton<ObjectManager>
{
public:
	/**
	 * @struct HierarchyData
	 * @brief ヒエラルキーのデータ用
	 */
	struct HierarchyData
	{
		HierarchyData() = default;
		GameObject* gameObject;	//!< オブジェクトのデータ
		std::vector<HierarchyData> m_childList;	//!< 子オブジェクトの配列
	};
public:
	friend class Singleton<ObjectManager>;		//!< シングルトンクラスでの生成を可能に

private:
	std::unordered_map<std::string, std::unique_ptr<GameObject>> m_ObjList;	//!< オブジェクトリスト
	std::vector<GameObject*> m_ObjListBuffer;	//!< オブジェクト生成時の一時保存用バッファ

	std::vector<HierarchyData> m_hierarchy;		//!< ヒエラルキー(Init,Update用)
	int m_cntHierarchy;							//!< ヒエラルキーのデータ数

private:

	/**
	 * @brief ヒエラルキーの作成
	 * @return なし
	 */
	void CreateHierarchy();

	/**
	 * @brief ヒエラルキーにデータをセット
	 * @param[in] obj セットするデータ
	 * @return なし
	 */
	void SetHierarchy(GameObject* obj);

	/**
	 * @brief 一時保存されてるオブジェクトの初期化処理
	 * @return なし
	 */
	void InitObjectBuffer();

	/**
	 * @brief 一時保存されているオブジェクトをリストに登録
	 * @return なし
	 */
	void MergeObjList();

	/**
	 * @brief オブジェクトが所属しているヒエラルキーの階層データを取得
	 * @param[in] data 階層データ
	 * @param[in] obj 探し出すオブジェクトデータ
	 * @return オブジェクトが所属している階層のデータ
	 */
	std::vector<ObjectManager::HierarchyData>* GetVectorData(std::vector<ObjectManager::HierarchyData>& data, GameObject * obj);

	/**
	 * @brief オブジェクトが所属しているヒエラルキーの階層データを取得
	 * @param[in] obj探し出したいオブジェクトデータ
	 * @return ヒエラルキー階層データ
	 */
	std::vector<ObjectManager::HierarchyData>* GetHierarchyData(GameObject * obj);

	/**
	 * @brief オブジェクトのヒエラルキーデータを取得する再帰関数
	 * @param[in] data ヒエラルキーの階層データ
	 * @param[in] obj ほしいデータのオブジェクト
	 * @return ヒエラルキーに入っているオブジェクトに対応したデータ
	 */
	HierarchyData* FindDataInHierarchy(std::vector<HierarchyData>& data, GameObject * obj);

public:

	/**
	 * @brief ヒエラルキーにあるオブジェクトの数の取得
	 * @return オブジェクト数
	 */
	int GetHierarchyCnt() {
		return m_cntHierarchy;
	}

	/**
	 * @brief オブジェクトリストの取得
	 * @return オブジェクトリスト
	 */
	std::unordered_map<std::string, std::unique_ptr<GameObject>>& GetObjList() {
		return m_ObjList;
	}

	/**
	 * @brief ヒエラルキーの取得
	 * @return ヒエラルキーデータ
	 */
	std::vector<HierarchyData>& GetHierarchy(){
		return m_hierarchy;
	}

	/**
	 * @brief オブジェクトの生成
	 * @param[in] name オブジェクト名
	 * @return 生成したオブジェクトの実体
	 */
	template <class T>
	static T* Create(std::string name)
	{
		T* work = new T();
		int num = 0;
		std::string keyName = name;
		GameObject* obj;

		ObjectManager::GetInstance().m_ObjListBuffer.push_back(work);
		obj = dynamic_cast<GameObject*>(ObjectManager::GetInstance().m_ObjListBuffer.back());
		obj->SetName(name);
		ObjectManager::GetInstance().SetHierarchy(obj);
		obj->Awake();

		return dynamic_cast<T*>(obj);
	}

	/**
	 * @brief オブジェクトの取得
	 * @param[in] name 取得したいオブジェクトの名前
	 * @retrun オブジェクトのポインタ
	 */
	template <class T>
	T* FindObject(std::string name)
	{
		if (m_ObjList.find(name) == m_ObjList.end()) {
			return nullptr;
		}
		return dynamic_cast<T*>(m_ObjList[name].get());
	}

	/**
	 * @breif オブジェクトリストのクリア
	 * @return なし
	 */
	static void Clear();

	/**
	 * @biref オブジェクトを親のヒエラルキーデータの子供にセット
	 * @param[in] parent　セットする親オブジェクトのデータ
	 * @param[in] childObj セットする子オブジェクトのデーター
	 * @return なし
	 */
	void SetParent(GameObject* parent, GameObject* childObj);

	/**
	 * @brief ヒエラルキーの更新処理
	 * @return なし
	 */
	void UpdateHierarchy(std::vector<ObjectManager::HierarchyData> data);

	/**
	 * @brief ヒエラルキーの遅れた更新処理
	 * @return なし
	 */
	void LateUpdateHierarchy(std::vector<ObjectManager::HierarchyData> data);

	/**
	 * @brief ヒエラルキーから子オブジェクトを探し出す
	 * @param[in] findObj 探し出す親のオブジェクト
	 * @param[in] index 子オブジェクトの番号
	 * @return 子オブジェクトのデータ
	 */
	GameObject* FindChildInHierarchy(GameObject* findObj, int index);

	/**
	 * @brief ヒエラルキーから子オブジェクトを取得
	 * @param[in] findObj 探し出す親データ
	 * @param[in] name 子オブジェクトの名前
	 * @return nameに対応した子オブジェクト
	 */
	GameObject * FindChildInHierarchy(GameObject * findObj, std::string name);

	/**
	 * @brief コンストラクタ
	 */
	ObjectManager() {
		m_cntHierarchy = 0;
	}

	/**
	 * @brief 初期化処理
	 * @return　なし
	 */
	void Awake();

	/**
	 * @brief 初期化処理
	 * @return　なし
	 */
	HRESULT Init();


	/**
	 * @brief 終了処理
	 * @return　なし
	 */
	void Uninit();

	/**
	 * @brief 更新処理
	 * @return　なし
	 */
	void Update();
	
	/**
	 * @brief 更新処理
	 * @return なし
	 * @details 座標更新、当たり判定後の処理内容を記述する
	 */
	void LastUpdate();
	
	/**
	 * @brief 描画処理
	 * @return　なし
	 */
	void Draw();

	void DrawShadow();
	
	std::list<GameObject*> FindObjectsWithTag(int tag);

	/**
	 * @brief オブジェクトの取得
	 * @param[in] tag　オブジェクトの識別タグ
	 * @return 見つけ出したオブジェクト　何もなければnullptr
	 */
	GameObject* FindWithTag(int tag);
};

// EOF