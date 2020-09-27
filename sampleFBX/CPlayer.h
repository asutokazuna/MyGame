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

class PlayerMissile;
class Collision;

class CPlayer: public GameObject
{
private:
	XMFLOAT3 m_vCenter;		//!< 境界ボックス中心座標
	XMFLOAT3 m_vBBox;		//!< 境界ボックスサイズ
	CBox m_box;				//!< 境界ボックス

	XMFLOAT3 m_vPosBBox;	//!< 境界ボックス中心座標（）
	bool m_bHit;			//!< 衝突の有無

private:
	std::list<PlayerMissile*> m_Missile;
	Collision* m_col;

public:
	CPlayer();
	HRESULT Init();
	void Update();
};

// EOF