/**
 * @file BattleCamera.cpp
 * @brief 戦闘中のカメラ
 */
#pragma once
#include "CCamera.h"

// 前方宣言
class Transform;

/**
 * @class BattleCamera
 * @brief 戦闘中のカメラ制御
 */
class BattleCamera :public CCamera
{
private:
	Transform* m_target;	//!< 追跡する対象
	Vector3 m_rect;			//!< 対象を追う範囲
	Vector3 m_Cursor;		//!< ロックオン範囲
public:
	/**
	* @brief 初期化処理
	* @return なし
	*/
	virtual void Awake();

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	virtual HRESULT Init();

	/**
	 * @brief 更新処理
	 * @return なし
	 */
	void Update();
};

// EOF