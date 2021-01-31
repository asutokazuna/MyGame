/*
 *@file ObjectManager.h
 * @brief オブジェクト管理クラス
 */
#include "ObjectManager.h"
#include "ObjectRenderer.h"

void ObjectManager::CreateHierarchy()
{
	Object* workObj;				//!< オブジェクト格納用
	HierarchyData data = HierarchyData();

	for (auto &obj : m_ObjList)
	{
		data.gameObject = obj.second.get();
		// ヒエラルキーにセット
		m_hierarchy.push_back(data);
		// ワークをクリア
		data = HierarchyData();
	}
}

void ObjectManager::SetHierarchy(GameObject* obj)
{
	HierarchyData data = HierarchyData();
	data.gameObject = obj;
	m_hierarchy.push_back(data);
}

GameObject* ObjectManager::FindChildInHierarchy(GameObject* findObj, int index)
{
	for (auto objInHierarchy : m_hierarchy)
	{
		if (objInHierarchy.gameObject == findObj)
		{
			return objInHierarchy.m_childList.at(index).gameObject;
		}
	}
}

void ObjectManager::SetParent(GameObject * parent, GameObject * childObj)
{
	GameObject* workchild = nullptr;
	GameObject* root = childObj->GetRoot();
	HierarchyData childData;

	// 子オブジェクトのデータを探し出しリストから削除
	for (auto itHierarchy = m_hierarchy.begin(); itHierarchy != m_hierarchy.end(); itHierarchy++)
	{
		// 親階層で検索
		if (itHierarchy->gameObject == childObj)
		{
			childData = *itHierarchy;
			itHierarchy = m_hierarchy.erase(itHierarchy);
			break;
		}

		// 子階層で検索
		for (auto inChild = itHierarchy->m_childList.begin(); inChild != itHierarchy->m_childList.end(); inChild++)
		{
			if (inChild->gameObject== childObj)
			{
				childData = *inChild;
				itHierarchy->m_childList.erase(itHierarchy);
				break;
			}
		}
	}

	// 子にセット
	for (auto hierarchyObj : m_hierarchy)
	{
		if (hierarchyObj.gameObject == root)
		{
			if (hierarchyObj.gameObject == parent) {
				hierarchyObj.m_childList.push_back(childData);
			}
			for (auto inChild : hierarchyObj.m_childList)
			{
				if (inChild.gameObject == parent) {
					inChild.m_childList.push_back(childData);
				}
			}
		}
	}
}
/**
 * @brief 初期化処理
 * @return　なし
 */
void ObjectManager::Awake()
{
	/**
	 * objectのAwake処理はCreate時に呼んでいるため処理しない
	 */

	//auto& buff = m_ObjList;
	//for (auto& obj : buff) {
	//	obj.second.get()->Awake();
	//}
}

/**
 * @brief 初期化処理
 * @return　なし
 */
 HRESULT ObjectManager::Init()
{
	 //CreateHierarchy();
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
	ObjectRenderer::GetInstance().Draw();
	//for (auto& obj : buff) {
	//	if (obj.second.get()->GetActive() == false) {
	//		continue;
	//	}
	//	obj.second.get()->Draw();

	//}
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