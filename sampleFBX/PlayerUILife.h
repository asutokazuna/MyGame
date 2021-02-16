/**
 * @class PlayerUILife
 * @breif プレイヤーのステータスをUIに表示するコンポーネント
 * @author Ariga
 */
#pragma once
#include "Component.h"

class GameObject;
class PlayerLifeCtrl;
class NumberListCtrl;

/**
 * @class PlayerUILife
 * @breif プレイヤーのステータスをUIに表示するコンポーネント
 */
class PlayerUILife :public Component
{
private:
	GameObject* m_playerObj;
	PlayerLifeCtrl* m_playerLife;
	GameObject* m_numberUI;
	GameObject* m_gauge;
	NumberListCtrl* m_LifeNum;

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