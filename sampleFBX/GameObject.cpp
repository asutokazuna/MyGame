/**
 * @file GameObject.h
 * @brief ゲームオブジェクト
 */
#include "GameObject.h"

/**
 * @brief コンストラクタ
 */
GameObject::GameObject() : parent(nullptr){
	transform = AddComponent<Transform>();
	tag = 0;
}

/**
 * @brief デストラクタ
 */
GameObject::~GameObject() {
	for (auto com : m_ComponentList)
		delete com;
}

/**
 * @brief 初期化処理
 * @return　なし
 */
HRESULT GameObject::Init()
{
	auto buff = m_ComponentList;
	for (auto com : buff)
		com->Init();

	for (auto& child : m_ChildList) {
		child->Init();
	}

	return S_OK;
}

/**
 * @brief 終了処理
 * @return　なし
 */
void GameObject::Uninit()
{
	auto buff = m_ComponentList;
	for (auto com : buff)
		com->Uninit();

	for (auto& child : m_ChildList) {
		child->Uninit();
	}
}

/**
 * @brief 更新処理
 * @return  なし
 */
void GameObject::Update()
{
	if (this->GetActive() == false) {
		return;
	}
	auto buff = m_ComponentList;
	for (auto com : buff) {
		if (com->GetActive() == false) {
			continue;
		}
		com->Update();
	}
	
	for (auto& child : m_ChildList) {
		child->Update();
	}
}

/**
 * @brief 更新処理
 * @return  なし
 */
void GameObject::LateUpdate()
{
	if (this->GetActive() == false) {
		return;
	}
	auto buff = m_ComponentList;
	for (auto com : buff) {
		if (com->GetActive() == false) {
			continue;
		}
		com->LateUpdate();
	}

	for (auto& child : m_ChildList) {
		child->LateUpdate();
	}
}

/**
 * @brief 描画処理
 * @return  なし
 */
void GameObject::Draw()
{
	if (this->GetActive() == false) {
		return;
	}
	for (auto com : m_ComponentList) {
		if (com->GetActive() == false) {
			continue;
		}
		com->Draw();
	}

	for (auto& child : m_ChildList) {
		child->Draw();
	}
}

/**
 * @brief 描画処理
 * @return  なし
 */
void GameObject::DrawAlpha()
{
	if (this->GetActive() == false) {
		return;
	}
	for (auto com : m_ComponentList) {
		if (com->GetActive() == false) {
			continue;
		}
		com->DrawAlpha();
	}

	for (auto& child : m_ChildList) {
		child->DrawAlpha();
	}
}

/**
 * @brief 子オブジェクトの設定
 * @return なし
 */
 void GameObject::SetChild(GameObject * child)
 {
	 std::unique_ptr<GameObject> buff(child);

	 buff->parent = this;
	 buff->Awake();
	 m_ChildList.push_back(std::move(buff));
 }

 /**
  * @brief トランスフォームの取得
  * @return トランスフォーム
  */
 Transform& GameObject::GetTransform() {
	 return *transform;
 }

 /**
  * @brief 当たり判定処理
  * @return なし
  */
 void GameObject::OnCollisionEnter(GameObject * gameObbj)
 {
	 for (auto com : m_ComponentList)
		 com->OnCollisionEnter(gameObbj);

	 for (auto& child : m_ChildList) {
		 child->OnCollisionEnter(gameObbj);
	 }
 }

 /**
  * @brief タグの比較
  * @return 一致していればtrue
  */
 bool GameObject::CompareTag(int objTag)
 {
	 return objTag == tag;
 }

// EOF