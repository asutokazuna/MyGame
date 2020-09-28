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
	auto& buff = ObjectManager::GetInstance().m_ObjList;
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
	 auto& buff = ObjectManager::GetInstance().m_ObjList;
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
	auto& buff = ObjectManager::GetInstance().m_ObjList;
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
	auto& buff = ObjectManager::GetInstance().m_ObjList;
	for (auto& obj : buff) {
		obj.second.get()->Update();
	}
	for (auto& obj : buff) {
		obj.second.get()->LateUpdate();
	}
}
	
/**
 * @brief 描画処理
 * @return　なし
 */
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