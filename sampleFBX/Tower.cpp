/**
 * @file Tower
 * @brief Towerクラス
 */
#include "Tower.h"
#include "Object3D.h"
#include "ModelData.h"
#include "TowerEnergy.h"
#include "Gauge.h"
#include "TowerCtrl.h"
#include "collision.h"

 /**
  * @brief 初期化処理
  * @return なし
  */
void Tower::Awake()
{
	tag = OBJ_TAG_TOWER;

	m_Object3D = &AddComponent<Object3D>()->SetModel(MODEL_TOWER);
	transform->scale = 0.5f;
	m_collision = AddComponent<Collision>();
	m_Energy = AddComponent<TowerEnergy>();
	m_LifeGauge = new Gauge();
	m_ctrl = AddComponent<TowerCtrl>();
	SetChild(m_LifeGauge);
	m_LifeGauge->SetOffset({ 0, 150, 0 });
	Vector3 blue = Vector3(0, 0, 1);
	Vector3 red = Vector3(1, 0, 0);
	m_LifeGauge->SetParam(ENERGY_MAX, 0, blue, red);

	m_collision->SetModelKind(MODEL_TOWER);
}

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT Tower::Init()
{
	m_LifeGauge->SetTransform(transform);
	m_LifeGauge->SetValue(m_Energy->GetEnergy());
	GameObject::Init();

	return E_NOTIMPL;
}

// EOF