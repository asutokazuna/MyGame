/*
 *@file ObjectManager.h
 * @brief オブジェクト管理クラス
 * @author Ariga
 */
#include "ObjectManager.h"
#include "ObjectRenderer.h"

void ObjectManager::CreateHierarchy()
{
	//HierarchyData data = HierarchyData();

	//for (auto &obj : m_ObjList)
	//{
	//	data.gameObject = obj.second.get();
	//	// ヒエラルキーにセット
	//	m_hierarchy.push_back(data);
	//	// ワークをクリア
	//	data = HierarchyData();
	//}
}

/**
 * @brief ヒエラルキーにデータをセット
 * @param[in] obj セットするデータ
 * @return なし
 */
void ObjectManager::SetHierarchy(GameObject* obj)
{
	HierarchyData data = HierarchyData();
	data.gameObject = obj;
	m_hierarchy.push_back(data);
	m_cntHierarchy++;
}

/**
 * @brief 一時保存されてるオブジェクトの初期化処理
 * @return なし
 */
void ObjectManager::InitObjectBuffer()
{
	if (m_ObjListBuffer.size() <= 0) {
		return;
	}

	for (int i = 0; i < m_ObjListBuffer.size(); i++)
	{
		m_ObjListBuffer.at(i)->Init();
	}
}

/**
 * @brief 一時保存されているオブジェクトをリストに登録
 * @return なし
 */
void ObjectManager::MergeObjList()
{	
	if (m_ObjListBuffer.size() <= 0) {
		return;
	}

	std::string keyName;
	int num = 0;
	std::string name;

	for (int i = 0; i < m_ObjListBuffer.size(); i++)
	{
		std::unique_ptr<GameObject> objPtr(m_ObjListBuffer.at(i));
		name = keyName = m_ObjListBuffer.at(i)->GetName();

		// 名前の重複確認
		while (m_ObjList.find(keyName) != m_ObjList.end())
		{
			//keyName.clear();
			keyName = name + std::to_string(num);
			num++;
		}
		// 登録
		m_ObjList[keyName] = std::move(objPtr);
	}

	m_ObjListBuffer.clear();
}

/**
 * @brief ヒエラルキーから子オブジェクトを探し出す
 * @param[in] findObj 探し出す親のオブジェクト
 * @param[in] index 子オブジェクトの番号
 * @return 子オブジェクトのデータ
 */
GameObject* ObjectManager::FindChildInHierarchy(GameObject* findObj, int index)
{
	for (auto objInHierarchy : m_hierarchy)
	{
		if (objInHierarchy.gameObject == findObj)
		{
			try {
				objInHierarchy.m_childList.at(index);
			}
			catch (std::out_of_range){
				return nullptr;
			}

			return objInHierarchy.m_childList.at(index).gameObject;
		}
	}
	return nullptr;
}

/**
 * @brief オブジェクトのヒエラルキーデータを取得する再帰関数
 * @param[in] data ヒエラルキーの階層データ
 * @param[in] obj ほしいデータのオブジェクト
 * @return ヒエラルキーに入っているオブジェクトに対応したデータ
 */
ObjectManager::HierarchyData* ObjectManager::FindDataInHierarchy(std::vector<HierarchyData>& data, GameObject* obj)
{
	GameObject* root = obj->GetRoot();
	HierarchyData* result = nullptr;

	for (auto& objInData : data)
	{
		if (objInData.gameObject->GetRoot() == root)
		{
			if (objInData.gameObject == obj) {
				result = &objInData;
				break;
			}

			result = FindDataInHierarchy(objInData.m_childList, obj);
			if (result != nullptr) {
				break;
			}
		}
	}

	return result;
}

/**
 * @brief オブジェクトが所属しているヒエラルキーの階層データを取得
 * @param[in] data 階層データ
 * @param[in] obj 探し出すオブジェクトデータ
 * @return オブジェクトが所属している階層のデータ
 */
std::vector<ObjectManager::HierarchyData>* ObjectManager::GetVectorData(std::vector<ObjectManager::HierarchyData>& data, GameObject* obj)
{
	std::vector<HierarchyData>* result = nullptr;

	for (auto inData : data)
	{
		if (inData.gameObject == obj)
		{
			result = &data;
			break;
		}
		else if (inData.gameObject == obj)
		{
			result = GetVectorData(inData.m_childList, obj);
			if (result != nullptr) {
				break;
			}
		}
	}

	return result;
}

/**
 * @brief オブジェクトが所属しているヒエラルキーの階層データを取得
 * @param[in] obj探し出したいオブジェクトデータ
 * @return ヒエラルキー階層データ
 */
std::vector<ObjectManager::HierarchyData>* ObjectManager::GetHierarchyData(GameObject* obj)
{
	GameObject* root = obj->GetRoot();
	std::vector<ObjectManager::HierarchyData>* result = nullptr;

	for (auto inData : m_hierarchy)
	{
		if (inData.gameObject == obj)
		{
			result = &m_hierarchy;
		}
		else if (inData.gameObject == root)
		{
			result = GetVectorData(inData.m_childList, obj);
		}
	}
	return result;
}

/**
 * @brief ヒエラルキーから子オブジェクトを取得
 * @param[in] findObj 探し出す親データ
 * @param[in] name 子オブジェクトの名前
 * @return nameに対応した子オブジェクト
 */
GameObject* ObjectManager::FindChildInHierarchy(GameObject* findObj, std::string name)
{
	GameObject* work = nullptr;
	HierarchyData* findData ;

	// 親オブジェクトの取得
	findData = FindDataInHierarchy(m_hierarchy, findObj);

	// 親が存在しない
	if (findData->gameObject == nullptr) {
		return nullptr;
	}

	for (auto obj : findData->m_childList)
	{
		if (obj.gameObject->GetName() == name)
		{
			return obj.gameObject;
		}
	}

	return nullptr;
}

/**
 * @brief リストの消去
 * @return なし
 */
void ObjectManager::Clear()
{
	ObjectManager::GetInstance().m_ObjList.clear();
	ObjectManager::GetInstance().m_hierarchy.clear();
	ObjectManager::GetInstance().m_ObjListBuffer.clear();
	ObjectManager::GetInstance().m_cntHierarchy = 0;
}

/**
 * @biref オブジェクトを親のヒエラルキーデータの子供にセット
 * @param[in] parent　セットする親オブジェクトのデータ
 * @param[in] childObj セットする子オブジェクトのデーター
 * @return なし
 */
void ObjectManager::SetParent(GameObject * parent, GameObject * childObj)
{
	GameObject* workchild = nullptr;
	GameObject* root = childObj->GetRoot();
	HierarchyData childData;
	std::vector<HierarchyData>* vecParent = nullptr;

	vecParent = GetHierarchyData(childObj);

	if (vecParent == nullptr) {
		return;
	}

	for (auto objit = vecParent->begin(); objit != vecParent->end(); objit++)
	{
		if (objit->gameObject == childObj)
		{
			childData = *objit;
			vecParent->erase(objit);
			break;
		}
	}

	// 子にセット
	HierarchyData* parentData = FindDataInHierarchy(m_hierarchy, parent);

	parentData->m_childList.push_back(childData);
	for (auto objInChild : childData.m_childList)
	{
		objInChild.gameObject->SetRoot(parentData->gameObject->GetRoot());
	}
}

/**
 * @brief ヒエラルキーの更新処理
 * @return なし
 */
void ObjectManager::UpdateHierarchy(std::vector<ObjectManager::HierarchyData> data)
{
	for (auto o : data)
	{
		o.gameObject->Update();
		UpdateHierarchy(o.m_childList);
	}
}

/**
 * @brief ヒエラルキーの遅れた更新処理
 * @return なし
 */
void ObjectManager::LateUpdateHierarchy(std::vector<ObjectManager::HierarchyData> data)
{
	for (auto o : data)
	{
		o.gameObject->LateUpdate();
		LateUpdateHierarchy(o.m_childList);
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
	MergeObjList();

	auto& buff = m_ObjList;
	for (auto& obj : buff) {
		obj.second.get()->Init();
	}

	InitObjectBuffer();
	MergeObjList();

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
	UpdateHierarchy(m_hierarchy);

	LateUpdateHierarchy(m_hierarchy);

	InitObjectBuffer();
	MergeObjList();
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
	//for (auto& obj : buff) {
	//	if (obj.second.get()->GetActive() == false) {
	//		continue;
	//	}
	//	obj.second.get()->DrawAlpha();
	//}
#ifdef _DEBUG
	if (ImGui::TreeNode("ObjectName")) {
		for (auto& obj : buff) {
			ImGui::Text("%s\n", obj.first.c_str());
		}
		ImGui::TreePop();
	}
#endif
}

/**
 * @brief オブジェクトを探し出す

 * @return 見つけ出したオブジェクトデータ
 */
GameObject* Find(GameObject* obj, int tag)
{
	GameObject* work = nullptr;

	if (obj->GetTag() == tag)
	{
		return obj;
	}

	//for (auto& child : obj->GetChildList())
	//{
	//
	//	work = Find(child, tag);
	//	if (work != nullptr) {
	//		break;
	//	}
	//}

	return work;
}

std::list<GameObject*> Finds(GameObject* obj, int tag)
{
	std::list<GameObject*> work;
	if (obj->GetTag() == tag)
	{
		work.push_back(obj);
	}

	//for (auto& child : obj->GetChildList())
	//{
	//	work.merge(Finds(child,tag));
	//}

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

/**
 * @brief オブジェクトの取得
 * @param[in] tag　オブジェクトの識別タグ
 * @return 見つけ出したオブジェクト　何もなければnullptr
 */
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