/**
 * @file PlayerMove
 * @brief プレイヤーの移動
 */
#pragma once
#include "Component.h"

class Transform;
class PlayerMove: public Component
{
private:
	Transform* m_Transform;
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