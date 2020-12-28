/**
 * @file PlayerLifeUI
 * @brief HPの表示
 */
#pragma once
#include "Component.h"
#include <list>

class PlayerLifeCtrl;

/**
 * @class PlayerLifeUI
 * @brief HPの表示
 */
class PlayerLifeUI :public Component
{
private:
	std::list<GameObject*> m_NumberList;		//!< ライフ表示オブジェクト
	PlayerLifeCtrl* m_lifeCtrl;
public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 更新処理
	 * @return なし
	 */
	void Update();
};

// EOF