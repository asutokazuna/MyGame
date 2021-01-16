/*
 *@file ObjectManager.h
 * @brief オブジェクト管理クラス
 */
#include "ObjectManager.h"

/**
 * @brief 初期化処理
 * @return　なし
 */
void ObjectManager::Awake()
{
	auto& buff = m_ObjList;
	for (auto& obj : buff) {
		obj.second.get()->Awake();
	}
}

/**
 * @brief 初期化処理
 * @return　なし
 */
 HRESULT ObjectManager::Init()
{
	 auto& buff = m_ObjList;
	for (auto& obj : buff) {
		obj.second.get()->Init();
	}

	return E_NOTIMPL;
}

/**
 * @brief 終了処理
 * @return　なし
 */
void ObjectManager::Uninit()
{
	auto& buff = m_ObjList;
	for (auto& obj : buff) {
		obj.second.get()->Uninit();
	}
}

/**
 * @brief 更新処理
 * @return　なし
 */
void ObjectManager::Update()
{
	auto& buff = m_ObjList;
	for (auto& obj : buff) {
		if (obj.second.get()->GetActive() == false) {
			continue;
		}
		obj.second.get()->Update();
	}
	for (auto& obj : buff) {
		if (obj.second.get()->GetActive() == false) {
			continue;
		}
		obj.second.get()->LateUpdate();
	}
}

/**
 * @brief 更新処理
 * @return なし
 * @details 座標更新、当たり判定後の処理内容を記述する
 */
void ObjectManager::LastUpdate()
{
	auto& buff = m_ObjList;
	for (auto& obj : buff) {
		if (obj.second.get()->GetActive() == false) {
			continue;
		}
		obj.second.get()->LastUpdate();
	}
}
	
/**
 * @brief 描画処理
 * @return　なし
 */
void ObjectManager::Draw()
{
	auto& buff = m_ObjList;
	for (auto& obj : buff) {
		if (obj.second.get()->GetActive() == false) {
			continue;
		}
		obj.second.get()->Draw();

	}
	for (auto& obj : buff) {
		if (obj.second.get()->GetActive() == false) {
			continue;
		}
		obj.second.get()->DrawAlpha();
	}
#ifdef _DEBUG
	if (ImGui::TreeNode("ObjectName")) {
		for (auto& obj : buff) {
			ImGui::Text("%s\n", obj.first.c_str());
		}
		ImGui::TreePop();
	}
#endif
}

GameObject* Find(GameObject* obj, int tag)
{
	GameObject* work = nullptr;

	if (obj->GetTag() == tag)
	{
		return obj;
	}

	for (auto& child : obj->GetChildList())
	{
	
		work = Find(child, tag);
		if (work != nullptr) {
			break;
		}
	}

	return work;
}

std::list<GameObject*> Finds(GameObject* obj, int tag)
{
	std::list<GameObject*> work;
	if (obj->GetTag() == tag)
	{
		work.push_back(obj);
	}

	for (auto& child : obj->GetChildList())
	{
		work.merge(Finds(child,tag));
	}

	return work;
}

std::list<GameObject*> ObjectManager::FindObjectsWithTag(int tag)
{
	std::list<GameObject*> result;
	GameObject* work;

	auto& buff = m_ObjList;
	for (auto& obj : buff) {
		work = dynamic_cast<GameObject*>(obj.second.get());

		result.merge(Finds(work,tag));
	}
	return result;
}

 GameObject* ObjectManager::FindWithTag(int tag)
 {
	 GameObject* resultObj = nullptr;
	 GameObject* work;

	 auto& buff = m_ObjList;
	 for (auto& obj : buff) {
		 work = dynamic_cast<GameObject*>(obj.second.get());
		 resultObj = Find(work, tag);
		 if (resultObj != nullptr) {
			 break;
		 }
	 }
	 return resultObj;
 }

// EOF