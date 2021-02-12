/*
 *@file ObjectManager.h
 * @brief オブジェクト管理クラス
 */
#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <memory>
#include "GameObject.h"
#include <list>
#include <vector>
#include <string>
#include <map>

class Object;

/*
 *@class objectManager
 * @brief オブジェクト管理クラス
 */
class ObjectManager : public Singleton<ObjectManager>
{
public:
	struct HierarchyData
	{
		HierarchyData() = default;
		GameObject* gameObject;
		std::vector<HierarchyData> m_childList;
	};
public:
	friend class Singleton<ObjectManager>;		//!< シングルトンクラスでの生成を可能に

private:
	std::unordered_map<std::string, std::unique_ptr<GameObject>> m_ObjList;
	std::vector<GameObject*> m_ObjListBuffer;
	//std::unordered_map<std::string, std::unique_ptr<Object>> m_DontDestroyObjList;    // あとでやるかも

	std::vector<HierarchyData> m_hierarchy;
	int m_cntHierarchy;

private:

	/**
	 * @brief ヒエラルキーの作成
	 * @return なし
	 */
	void CreateHierarchy();

	void SetHierarchy(GameObject* obj);

	void InitMergeObject();

public:

	int GetHierarchyCnt() {
		return m_cntHierarchy;
	}

	std::unordered_map<std::string, std::unique_ptr<GameObject>>& GetObjList() {
		return m_ObjList;
	}
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

	void MergeObjList();
	
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

	//void SetChild(GameObject* parent, GameObject* child);

	void SetParent(GameObject* parent, GameObject* childObj);

	void UpdateHierarchy(std::vector<ObjectManager::HierarchyData> data);

	void LateUpdateHierarchy(std::vector<ObjectManager::HierarchyData> data);

	GameObject* FindChildInHierarchy(GameObject* findObj, int index);

	HierarchyData* FindDataInHierarchy(std::vector<HierarchyData>& data, GameObject * obj);

	std::vector<ObjectManager::HierarchyData>* GetVectorData(std::vector<ObjectManager::HierarchyData>& data, GameObject * obj);

	//std::vector<ObjectManager::HierarchyData>& GetHierarchyData(std::vector<ObjectManager::HierarchyData> data, GameObject * obj);
	//
	//std::vector<ObjectManager::HierarchyData>& GetHierarchyData(std::vector<ObjectManager::HierarchyData> data, GameObject * obj, GameObject * parent);

	std::vector<ObjectManager::HierarchyData>* GetHierarchyData(GameObject * obj);

	GameObject * FindChildInHierarchy(GameObject * findObj, std::string name);

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
	 * @param[in] tag 取得したいオブジェクトのタグ
	 * @retrun オブジェクトのポインタ
	 */
	GameObject* FindWithTag(int tag);
};

// EOF