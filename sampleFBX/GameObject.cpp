/**
 * @file GameObject.h
 * @brief ゲームオブジェクト
 */
#include "GameObject.h"

/**
 * @brief コンストラクタ
 */
GameObject::GameObject() {
	transform = AddComponent<Transform>();
}

/**
 * @brief デストラクタ
 */
GameObject::~GameObject() {
	for (auto com : m_ComponentList)
		delete com;

	//for (auto child : m_ChildList) {
	//	delete child;
	//}

}

/**
 * @brief 更新処理
 * @return  なし
 */
void GameObject::Update()
{
	auto buff = m_ComponentList;
	for (auto com : buff)
		com->Update();
	
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
	auto buff = m_ComponentList;
	for (auto com : buff)
		com->LateUpdate();

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
	for (auto com : m_ComponentList)
		com->Draw();

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
	for (auto com : m_ComponentList)
		com->DrawAlpha();

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

	 buff->Init();
	 m_ChildList.push_back(std::move(buff));
	 //child->Init();
	 //m_ChildList.push_back(child);
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

// EOF