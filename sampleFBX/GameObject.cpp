/**
 * @file GameObject.h
 * @brief ゲームオブジェクト
 * @author Ariga
 */
#include "GameObject.h"
#include "ObjectManager.h"

/**
 * @brief コンストラクタ
 */
GameObject::GameObject() : parent(nullptr), root(this), childCount(0), m_castShadow(true), m_reciveShadow(true)
{
	transform = AddComponent<Transform>();
	transform->m_ParentTransform = transform;
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
}

/**
 * @brief 更新処理
 * @return なし
 * @details 座標更新、当たり判定後の処理内容を記述する
 */
 void GameObject::LastUpdate()
 {
	 if (this->GetActive() == false) {
		 return;
	 }
	 auto buff = m_ComponentList;
	 for (auto com : buff) {
		 if (com->GetActive() == false) {
			 continue;
		 }
		 com->LastUpdate();
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
}

/**
 * @brief 親オブジェクトの設定
 * @param[in] parent 親オブジェクト
 * @return なし
 */
void GameObject::SetParent(GameObject* parent)
{
	GameObject* workRoot = parent;
	this->parent = parent;
	
	parent->childCount++;
	while (workRoot != nullptr)
	{
	 this->root = workRoot->GetRoot();
	 workRoot = workRoot->GetParent();
	}
	
	ObjectManager::GetInstance().SetParent(parent, this);
}

GameObject* GameObject::GetChildTest(int index)
{
	GameObject* childObj = nullptr;

	childObj = ObjectManager::GetInstance().FindChildInHierarchy(this, index);

	return childObj;
}


GameObject* GameObject::GetChildTest(std::string name)
{
	GameObject* childObj = nullptr;

	childObj = ObjectManager::GetInstance().FindChildInHierarchy(this, name);

	return childObj;
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