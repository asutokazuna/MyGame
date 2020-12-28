/**
 * @file Tower
 * @brief Towerクラス
 */
#include "Tower.h"
#include "Object3D.h"
#include "ModelData.h"
#include "TowerEnergy.h"
#include "FbxModel.h"
#include "Gauge.h"
#include "TowerCtrl.h"
#include "collision.h"
#include "GaugeCtrl.h"

 /**
  * @brief 初期化処理
  * @return なし
  */
void Tower::Awake()
{
	tag = OBJ_TAG_TOWER;

	m_Object3D = &AddComponent<Object3D>()->SetModel(MODEL_TOWER);
	m_collision = AddComponent<Collision>()->SetSize({ 50,50,50 });
	m_Energy = AddComponent<TowerEnergy>();
	m_LifeGauge = new Gauge();
	m_ctrl = AddComponent<TowerCtrl>();
	SetChild(m_LifeGauge);
	m_LifeGauge->GetComponent<GaugeCtrl>()->SetOffset({ 0, 150, 0 });
}

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT Tower::Init()
{
	m_LifeGauge->GetComponent<GaugeCtrl>()->SetTarget(transform);
	GameObject::Init();

	return E_NOTIMPL;
}

// EOF