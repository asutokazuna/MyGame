/**
 * @file MissileMove
 * @brief ミサイルの動きクラス
 * @author Ariga
 */
#pragma once
#include "Component.h"

// 前方宣言
class Transform;

/**
 * @class MissileMove 
 * @brief ミサイルの動きを制御するコンポーネント
 */
class MissileMove :public Component
{
private:
	float m_Speed;		//!< 弾の移動速度

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
};

// EOF