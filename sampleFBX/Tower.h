/**
 * @file Tower
 * @brief TowerƒNƒ‰ƒX
 */
#pragma once
#include "GameObject.h"

class Object3D;
class TowerEnergy;
struct TFbxMaterial;
class TowerCollision;
class Gauge;

class Tower :public GameObject
{
private:
	Object3D* m_Object3D;
	XMFLOAT3 color;
	TFbxMaterial* material;
	TowerCollision* m_collision;
	Gauge*	m_LifeGauge;
public:
	TowerEnergy* m_Energy;
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void ChangeColor();
	Tower* SetPos(Vector3 pos);
};

// EOF