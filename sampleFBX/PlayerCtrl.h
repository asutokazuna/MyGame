/**
 * @file PlayerCtrl
 * @brief プレイヤーの制御クラス
 */
#pragma once
#include "Component.h"
#include <list>

 // 前方宣言
class PlayerMissile;
class Transform;

/**
 * @class PlayerCtrl
 * @brief プレイヤーの詳細な制御
 */
class PlayerCtrl: public Component
{
private:
	std::list<PlayerMissile*> m_Missile;	//!< ミサイル
	Transform* m_ParentTrans;				//!< 親の座標など

public:

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT InitParam(std::list<PlayerMissile*>& missile);

	/**
	 * @brief 更新処理
	 * @return なし
	 */
	void Update();
};

// EOF