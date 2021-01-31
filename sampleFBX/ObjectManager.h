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

class Object;

/*
 *@class objectManager
 * @brief オブジェクト管理クラス
 */
class ObjectManager : public Singleton<ObjectManager>
{
private:
	struct HierarchyData
	{
		HierarchyData() = default;
		GameObject* gameObject;
		std::vector<HierarchyData> m_childList;
	};
public:
	friend class Singleton<ObjectManager>;		//!< シングルトンクラスでの生成を可能に

public:
	std::unordered_map<std::string, std::unique_ptr<GameObject>> m_ObjList;
	//std::unordered_map<std::string, std::unique_ptr<Object>> m_DontDestroyObjList;    // あとでやるかも

	std::vector<HierarchyData> m_hierarchy;
private:

	/**
	 * @brief ヒエラルキーの作成
	 * @return なし
	 */
	void CreateHierarchy();

	void SetHierarchy(GameObject* obj);

public:

	/**
	 * @brief オブジェクトの生成
	 * @param[in] name オブジェクト名
	 * @return 生成したオブジェクトの実体
	 */
	template <class T>
	static T* Create(std::string name)
	{
		std::unique_ptr<T> work(new T());
		int num = 0;
		std::string keyName = name;
		GameObject* obj;

		while (ObjectManager::GetInstance().m_ObjList.find(keyName) != ObjectManager::GetInstance().m_ObjList.end())
		{
			keyName.clear();
			keyName = name + std::to_string(num);
			num++;
		}

		ObjectManager::GetInstance().m_ObjList[keyName] = std::move(work);
		obj = ObjectManager::GetInstance().m_ObjList[keyName].get();
		obj->SetName(name);
		ObjectManager::GetInstance().SetHierarchy(obj);
		obj->Awake();

		return dynamic_cast<T*>(ObjectManager::GetInstance().m_ObjList[keyName].get());
	}

	/**
	 * @brief オブジェクトの取得
	 * @param[in] name 取得したいオブジェクトの名前
	 * @retrun オブジェクトのポインタ
	 */
	template <class T>
	T* FindObject(std::string name)
	{
		return dynamic_cast<T*>(m_ObjList[name].get());
	}

	/**
	 * @breif オブジェクトリストのクリア
	 * @return なし
	 */
	static void Clear()
	{
		ObjectManager::GetInstance().m_ObjList.clear();
	}

	//void SetChild(GameObject* parent, GameObject* child);

	void SetParent(GameObject* parent, GameObject* childObj);

	GameObject* FindChildInHierarchy(GameObject* findObj, int index);

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