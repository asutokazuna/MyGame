/**
 * @file PlayerCtrl
 * @brief プレイヤーの制御クラス
 */
#pragma once
#include "Component.h"
#include <list>
#include <memory>
#include "MyMath.h"

 // 前方宣言
class Transform;

/**
 * @class PlayerCtrl
 * @brief プレイヤーの詳細な制御
 */
class PlayerCtrl: public Component
{
private:
	GameObject* m_Weapon;	//!< 武器オブジェクト
	GameObject* target;		//!< 弾を狙うターゲットオブジェクト
	Quaternion dir;			//!< 自分からターゲットへ向かう方向

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT Init();

	/**
	 * @brief 更新処理
	 * @return なし
	 */
	void Update();

	/**
	 * @brief 描画処理
	 * @return なし
	 */
	void Draw();

	/**
	 * @brief 弾発射
	 * @return なし
	 */
	void Attak();
};

// EOF