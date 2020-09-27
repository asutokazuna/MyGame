/*
 *@file ObjectManager.h
 * @brief オブジェクト管理クラス
 */
#include "ObjectManager.h"

HRESULT ObjectManager::Init()
{
	auto& buff = ObjectManager::GetInstance().m_ObjList;
	for (auto& obj : buff) {
		obj.second.get()->Awake();
	}

	for (auto& obj : buff) {
		obj.second.get()->Init();
	}

	return E_NOTIMPL;
}

void ObjectManager::Uninit()
{
	auto& buff = ObjectManager::GetInstance().m_ObjList;
	for (auto& obj : buff) {
		obj.second.get()->Uninit();
	}
}

void ObjectManager::Update()
{
	auto& buff = ObjectManager::GetInstance().m_ObjList;
	for (auto& obj : buff) {
		obj.second.get()->Update();
	}
	for (auto& obj : buff) {
		obj.second.get()->LateUpdate();
	}
}

void ObjectManager::Draw()
{
	auto& buff = ObjectManager::GetInstance().m_ObjList;
	for (auto& obj : buff) {
		obj.second.get()->Draw();
	}
	for (auto& obj : buff) {
		obj.second.get()->DrawAlpha();
	}
}

// EOF