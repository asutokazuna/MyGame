/**
 * @file Object.h
 * @brief ベースとなるオブジェクトクラス
 * @author Ariga
 */
#include "Object.h"

/**
 * @brief 削除関数
 * @return なし
 * @details 単純に削除するだけだと問題が出てくるため未実装
 */
void Object::Destroy(Object* obj) 
{
	//delete[] obj;
}

/**
 * @brief コンストラクタ
 */
 Object::Object():m_isActive(true), name("")
 {
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
 * @brief 更新処理
 * @return なし
 * @details 座標更新、当たり判定後の処理内容を記述する
 */
void Object::LastUpdate() {}

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