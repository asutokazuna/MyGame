/**
 * @file Object.h
 * @brief ベースとなるオブジェクトクラス
 * @author Ariga
 */
#pragma once
#include "main.h"
#include <string>

/**
 * @class Object
 * @breif ベースオブジェクト
 */
class Object
{
protected:
	bool m_isActive;		//!< アクティブかどうか
	std::string name;		//!< オブジェクト名

public:
	/**
	 * @brief 削除関数
	 * @return なし
	 * @details 単純に削除するだけだと問題が出てくるため未実装
	 */
	static void Destroy(Object* obj);

	/**
	 * @brief コンストラクタ
	 */
	Object();

	/**
	 * @brief デストラクタ
	 */
	virtual ~Object();

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	virtual void Awake();

	/**
	 * @brief 初期化処理
	 * @return　なし
	 */
	virtual HRESULT Init();

	/**
	 * @brief 終了処理
	 * @return　なし
	 */
	virtual void Uninit();

	/**
	 * @brief 更新処理
	 * @return　なし
	 */
	virtual void Update();

	/**
	 * @brief 更新処理
	 * @return　なし
	 */
	virtual void LateUpdate();

	/**
	 * @brief 更新処理
	 * @return なし
	 * @details 座標更新、当たり判定後の処理内容を記述する
	 */
	virtual void LastUpdate();

	/**
	 * @brief 描画処理
	 * @return　なし
	 */
	virtual void Draw();

	/**
	 * @brief 透明部分描画処理
	 * @return　なし
	 */
	virtual void DrawAlpha();

	/**
	 * @brief 有効化の切り替え
	 * @param[in] flg オブジェクトの有効化フラグ
	 * @return なし
	 */
	void SetActive(bool flg) {
		m_isActive = flg;
	}

	/**
	 * @brief フラグの取得
	 * @return オブジェクトが有効ならtrue
	 */
	bool GetActive() {
		return m_isActive;
	}

	/**
	 * @brief 名前のセット
	 * @return なし
	 */
	void SetName(std::string name) {
		this->name = name;
	}

	/**
	 * @brief 名前の取得
	 * @return 名前
	 */
	std::string GetName() {
		return name;
	}
};

// EOF