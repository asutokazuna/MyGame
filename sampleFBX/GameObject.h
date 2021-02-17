/**
 * @file GameObject.h
 * @brief ゲームオブジェクト
 * @author Ariga
 */
#pragma once
#include <list>
#include <memory>
#include "Component.h"
#include "Transform.h"
#include "Object.h"
#include <string>

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
	// TODO: transformにもっていく
	GameObject* parent;				//!< 親オブジェクト
	GameObject* root;				//!< 一番上の親オブジェクト
	int childCount;					//!< 子オブジェクトの数
	bool	m_castShadow;			//!< 影を落とすかどうか
	bool	m_reciveShadow;			//!< 影を受けるかどうか
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
	//void SetChild(GameObject* child);

	/**
	 * @brief 親オブジェクトのセット
	 * @return なし
	 */
	void SetParent(GameObject* parent);

	/**
	 * @brief 子オブジェクトの取得
	 * @param int index 子オブジェクトの格納差されている位置インデックス
	 * @return 子オブジェクト
	 */
	GameObject* GetChildTest(int index);

	/**
	 * @brief 子オブジェクトの取得
	 * @param name 子オブジェクトの名前
	 * @return 子オブジェクト
	 */
	GameObject * GetChildTest(std::string name);

	/**
	 * @brief 親の取得
	 * @return 親オブジェクト
	 */
	GameObject* GetParent() {
		return parent;
	}

	/**
	 * @brief ルートとなるオブジェクトのセット
	 * @return なし
	 */
	void SetRoot(GameObject* root) {
		this->root = root;
	}

	/**
	 * @brief ルートとなるオブジェクトの取得
	 * @return ルートオブジェクト
	 */
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
	 * @brief 影を落とすかどうか
	 * @return 影を落とす場合true
	 * @details レンダー専用のコンポーネントが作れた場合そちらに移動する
	 */
	bool IsCastShadow() {
		return m_castShadow;
	}

	/**
	 * @brief 影を落とすフラグをセット
	 * @param[in] flg 影を落としたいときはtrue
	 * @return なし
	 */
	void SetCastShadow(bool flg) {
		m_castShadow = flg;
	}

	/**
	 * @brief 影を受けるかどうか
	 * @return 影を受ける場合true
	 * @details レンダー専用のコンポーネントが作れた場合そちらに移動する
	 */
	bool IsReciveShadow() {
		return m_reciveShadow;
	}

	/**
	 * @brief 影を受けるフラグをセット
	 * @param[in] flg 影を受けたいときはtrue
	 * @return なし
	 */
	void SetReciveShadow(bool flg) {
		m_reciveShadow = flg;
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
};

// EOF