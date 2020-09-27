/**
 * @file Object.h
 * @brief ベースとなるオブジェクトクラス
 */
#include "Object.h"

void Object::Destroy(Object* obj) 
{
	//delete[] obj;
}

/**
 * @brief デストラクタ
 */
Object::~Object() {}

/**
 * @brief 初期化処理
 */
void Object::Awake() {}

/**
 * @brief 初期化処理
 * @return　なし
 */
HRESULT Object::Init() { return S_OK; }

/**
 * @brief 終了処理
 * @return　なし
 */
void Object::Uninit() {}

/**
 * @brief 更新処理
 * @return　なし
 */
void Object::Update() {}

/**
 * @brief 更新処理
 * @return　なし
 */
void Object::LateUpdate() {}

/**
 * @brief 描画処理
 * @return　なし
 */
void Object::Draw() {}

/**
 * @brief 透明部分描画処理
 * @return　なし
 */
void Object::DrawAlpha() {}

// EOF