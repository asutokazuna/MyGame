/**
 * @file CPlayer
 * @brief プレイヤークラス
 * @date 2020/06/19
 */
#pragma once
#include "Box.h"
#include "GameObject.h"
#include <memory>
#include <list>

// 前方宣言
class PlayerMissile;
class Collision;

/**
 * @class CPlayer
 * @brief プレイヤーのゲームオブジェクト
 */
class CPlayer: public GameObject
{
private:
	XMFLOAT3 m_vCenter;		//!< 境界ボックス中心座標
	XMFLOAT3 m_vBBox;		//!< 境界ボックスサイズ
	CBox m_box;				//!< 境界ボックス
private:
	std::list<PlayerMissile*> m_Missile;	//!< ミサイル
	Collision* m_col;						//!< コライダー

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

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
};

// EOF