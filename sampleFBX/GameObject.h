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
	Transform* transform;			//!< トランスフォーム
	int			tag;				//!< オブジェクト識別用タグ
	GameObject* parent;

public:
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
	 * @brief 親の取得
	 * @return 親オブジェクト
	 */
	GameObject* GetParent() {
		return parent;
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
		m_ComponentList.push_back(buff);
		buff->Awake();
		return buff;
	}

	/**
	 * @breif コンポーネントの取得
	 * @return クラスのコンポーネント
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

};

// EOF