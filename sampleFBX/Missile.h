/**
 * @file Missile
 * @brief ミサイルクラス
 * @date 2020/06/19
 */
#pragma once

#include "main.h"
#include "Box.h"
#include "GameObject.h"

class Collision;
class MissileMove;

class Missile: public GameObject
{
protected:
	Collision* m_col;
	MissileMove* m_Move;
public:
	Missile();
	~Missile();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void DrawAlpha();

	bool Fire(Vector3* pos);
	bool Fire(Vector3* pos, Quaternion quat);
};

// EOF