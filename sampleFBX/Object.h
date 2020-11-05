/**
 * @file Object.h
 * @brief ベースとなるオブジェクトクラス
 */
#pragma once
#include "main.h"

/**
 * @class Object
 * @breif ベースオブジェクト
 */
class Object
{
protected:
	bool m_isActive;		//!< アクティブかどうか

public:
	/**
	 * @brief 未実装
	 * @return なし
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

};

// EOF