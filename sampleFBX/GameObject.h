/**
 * @file GameObject.h
 * @brief コンポーネントオブジェクト
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
	Transform *transform;			//!< トランスフォーム

public:
	std::list<std::unique_ptr<GameObject>> m_ChildList;	//!< 子オブジェクトリスト

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
	 * @brief 更新処理
	 * @return  なし
	 */
	void Update();

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
	 * @brief トランスフォームの取得
	 * @return トランスフォーム
	 */
	Transform& GetTransform();

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
		buff->Init();
		return buff;
	}
};

// EOF