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
}

/**
 * @brief 描画処理
 * @return  なし
 */
void GameObject::Draw()
{
	for (auto com : m_ComponentList)
		com->Draw();
}

/**
 * @brief 描画処理
 * @return  なし
 */
void GameObject::DrawAlpha()
{
	for (auto com : m_ComponentList)
		com->DrawAlpha();
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
 }

 /**
  * @brief トランスフォームの取得
  * @return トランスフォーム
  */
 Transform& GameObject::GetTransform() {
	 return *transform;
 }

// EOF