/**
 * @file GameObject.h
 * @brief ゲームオブジェクト
 */
#pragma once
#include <list>
#include <memory>
#include "Component.h"
#include "Transform.h"
#include "Object.h"

/**
 * @class GameObject
 * @brief ゲームオブジェクト
 */
class GameObject :public Object
{
protected:
	Transform*	transform;			//!< トランスフォーム
	int			tag;				//!< オブジェクト識別用タグ
	int			layer;					//!< 所属レイヤー
	GameObject* parent;
	GameObject* root;
	int childCount;

private:
	std::list<std::unique_ptr<GameObject>> m_ChildList;	//!< 子オブジェクトリスト
	//std::list<GameObject*> m_ChildList;	//!< 子オブジェクトリスト

public:
	std::list<Component*> m_ComponentList;		//!< コンポーネントリスト

	/**
	 * @brief コンストラクタ
	 */
	GameObject();

	/**
	 * @brief デストラクタ
	 */
	~GameObject() override;

	/**
	 * @brief 初期化処理
	 * @return　なし
	 */
	HRESULT Init() override;

	/**
	 * @brief 終了処理
	 * @return　なし
	 */
	void Uninit();

	/**
	 * @brief 更新処理
	 * @return  なし
	 */
	void Update() override;

	/**
	 * @brief 更新処理
	 * @return  なし
	 */
	void LateUpdate() override;

	/**
	 * @brief 更新処理
	 * @return なし
	 * @details 座標更新、当たり判定後の処理内容を記述する
	 */
	void LastUpdate() override;

	/**
	 * @brief 描画処理
	 * @return  なし
	 */
	void Draw() override;

	/**
	 * @brief 描画処理
	 * @return  なし
	 */
	void DrawAlpha() override;

	/**
	 * @brief 子オブジェクトの設定
	 * @return なし
	 */
	void SetChild(GameObject* child);

	/**
	 * @brief 親オブジェクトのセット
	 * @return なし
	 */
	void SetParent(GameObject* parent);

	/**
	 * @brief 子オブジェクトの取得
	 * @param int index 子オブジェクトの格納差sれテイルインデックス
	 * @return 子オブジェクト
	 */
	GameObject* GetChildTest(int index);

	/**
	 * @brief 親の取得
	 * @return 親オブジェクト
	 */
	GameObject* GetParent() {
		return parent;
	}

	GameObject* GetRoot() {
		return root;
	}

	/**
	 * @brief トランスフォームの取得
	 * @return トランスフォーム
	 */
	Transform& GetTransform();

	/**
	 * @brief 当たり判定処理
	 * @return なし
	 */
	virtual void OnCollisionEnter(GameObject* gameObbj);

	/**
	 * @brief タグの比較
	 * @return 一致していればtrue
	 */
	bool CompareTag(int objTag);

	/**
	 * @brief タグの取得
	 * @return タグのID
	 */
	int GetTag() {
		return tag;
	}

	/**
	 * @brief タグのセット
	 * @return なし
	 */
	void SetTag(int tag) {
		this->tag = tag;
	}
	/**
	 * @brief レイヤーのセット
	 * @return なし
	 */
	void SetLayer(int layer) {
		this->layer = layer;
	}

	/**
	 * @brief レイヤーの取得
	 * @return なし
	 */
	int GetLayer() {
		return layer;
	}

	/**
	 * @breif コンポーネントの取得
	 * @return クラスのコンポーネント
	 */
	template<class T>
	T* GetComponent()
	{
		for (auto com : m_ComponentList)
		{
			T* buff = dynamic_cast<T*>(com);
			if (buff != nullptr)
				return buff;
		}
		return nullptr;
	}

	/**
	 * @brief コンポーネントの追加
	 * @return 追加したコンポーネントの実体
	 */
	template<class T>
	T* AddComponent()
	{
		T* buff = new T();
		buff->m_Parent = this;
		buff->m_ParentTransform = this->transform;
		m_ComponentList.push_back(buff);
		buff->Awake();
		return buff;
	}

	/**
	 * @breif 子オブジェクトの取得
	 * @return 子オブジェクト
	 */
	template<class T>
	T* GetChild()
	{
		for (auto& child : m_ChildList)
		{
			T* buff = dynamic_cast<T*>(child.get());
			if (buff != nullptr)
				return buff;
		}
		return nullptr;
	}

	/**
	 * @breif 子オブジェクトの取得
	 * @return 子オブジェクト
	 */
	template<class T>
	std::list<T*> GetChildren()
	{
		std::list<T*> work;

		for (auto& child : m_ChildList)
		{
			T* buff = dynamic_cast<T*>(child.get());
			if (buff != nullptr) {
				work.push_back(buff);
			}
		}
		return work;
	}

	/**
	 * @breif 子オブジェクトの取得
	 * @return 子オブジェクト
	 */
	template<class T>
	T* GetChild(std::string name)
	{
		for (auto& child : m_ChildList)
		{
			if (name == child->name)
			{
				T* buff = dynamic_cast<T*>(child.get());
				if (buff != nullptr)
					return buff;
			}
		}
		return nullptr;
	}

	/**
	 * @breif 子オブジェクトの取得
	 * @return 子オブジェクト
	 */
	GameObject* GetChild(int n)
	{
		int cnt = 0;
		for (auto& child : m_ChildList)
		{
			if (cnt == n) {
				return child.get();
			}
			cnt++;
		}
		return nullptr;
	}

	/**
	 * @breif 子オブジェクトの取得
	 * @return 子オブジェクト
	 */
	GameObject* GetChild(std::string name)
	{
		for (auto& child : m_ChildList)
		{
			if (name == child->name) {
				return child.get();
			}
		}
		return nullptr;
	}

	/**
	 * @brief 子オブジェクトのリストを取得
	 * @return 子オブジェクトリスト
	 */
	std::list<GameObject*> GetChildList() {
		std::list<GameObject*> work;

		for (auto& child : m_ChildList) {
			work.push_back(child.get());
		}

		return work;
	}

};

// EOF