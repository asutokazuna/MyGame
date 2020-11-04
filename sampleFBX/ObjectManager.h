/*
 *@file ObjectManager.h
 * @brief オブジェクト管理クラス
 */
#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <memory>
#include "GameObject.h"

class Object;

/*
 *@class objectManager
 * @brief オブジェクト管理クラス
 */
class ObjectManager : public Singleton<ObjectManager>
{
public:
	friend class Singleton<ObjectManager>;		//!< シングルトンクラスでの生成を可能に

private:
	std::unordered_map<std::string, std::unique_ptr<Object>> m_ObjList;
	//std::unordered_map<std::string, std::unique_ptr<Object>> m_DontDestroyObjList;    // あとでやる

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

		ObjectManager::GetInstance().m_ObjList[name] = std::move(work);
		return dynamic_cast<T*>(ObjectManager::GetInstance().m_ObjList[name].get());
	}

	/**
	 * @brief オブジェクトの取得
	 * @param[in] name 取得したいオブジェクトの名前
	 * @retrun オブジェクトのポインタ
	 */
	template <class T>
	static T* FindObject(std::string name)
	{
		return dynamic_cast<T*>(ObjectManager::GetInstance().m_ObjList[name].get());
	}

	/**
	 * @breif オブジェクトリストのクリア
	 * @return なし
	 */
	static void Clear()
	{
		ObjectManager::GetInstance().m_ObjList.clear();
	}

	/**
	 * @brief 初期化処理
	 * @return　なし
	 */
	static void Awake();

	/**
	 * @brief 初期化処理
	 * @return　なし
	 */
	static HRESULT Init();

	/**
	 * @brief 終了処理
	 * @return　なし
	 */
	static void Uninit();

	/**
	 * @brief 更新処理
	 * @return　なし
	 */
	static void Update();
	
	/**
	 * @brief 描画処理
	 * @return　なし
	 */
	static void Draw();

};

// EOF